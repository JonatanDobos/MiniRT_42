#include <scene.h>
#include <mathRT.h>
#include <render.h>

static bool	intersect_cylinder_caps(t_vec4 coords, t_vec4 orientation, t_vec4 plane_point, t_vec4 plane_normal, float *t)
{
	float denom = vdot(plane_normal, orientation);
	if (fabs(denom) > 1e-6) {
		t_vec4 p0l0 = plane_point - coords;
		*t = vdot(p0l0, plane_normal) / denom;
		return (*t >= 0);
	}
	return false;
}

static bool compute_cylinder_intersection(t_vec4 ray_vec, t_vec4 oc, t_vec4 ca, t_vec4 *quad_coeffs)
{
	// Step 2: Project ray direction and oc onto plane perpendicular to the cylinder axis
	t_vec4 rd = vsub(ray_vec, vscale(ca, vdot(ray_vec, ca))); // Projected ray direction
	t_vec4 oc_proj = vsub(oc, vscale(ca, vdot(oc, ca)));     // Projected oc

	// Step 3: Solve quadratic equation for the intersection
	(*quad_coeffs)[X] = vdot(rd, rd); // a
	(*quad_coeffs)[Y] = 2.0F * vdot(rd, oc_proj); // b
	(*quad_coeffs)[Z] = vdot(oc_proj, oc_proj) - (*quad_coeffs)[W]; // c
	(*quad_coeffs)[W] = (*quad_coeffs)[Y] * (*quad_coeffs)[Y] - 4.0F * (*quad_coeffs)[X] * (*quad_coeffs)[Z];

	return ((*quad_coeffs)[W] >= 0.0F); // Return true if there is an intersection
}

uint8_t ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t)
{
	// Step 1: Compute vectors for the cylinder's axis
	t_vec4 oc = vsub(ray.origin, obj->coords); // Vector from ray origin to obj->cylinder center
	t_vec4 ca = vnorm(obj->cylinder.orientation); // Cylinder axis (normalized)
	
	// Step 2: Project ray direction and oc onto plane perpendicular to the cylinder axis
	// t_vec4 rd = vsub(ray.vec, vscale(ca, vdot(ray.vec, ca))); // Projected ray direction
	// t_vec4 oc_proj = vsub(oc, vscale(ca, vdot(oc, ca)));     // Projected oc

	// Step 3: Solve quadratic equation for the intersection
	t_vec4	quadratic_coefficients;
	// quadratic_coefficients[X] = vdot(rd, rd);
	// quadratic_coefficients[Y] = 2.0F * vdot(rd, oc_proj);
	// quadratic_coefficients[Z] = vdot(oc_proj, oc_proj) - (obj->cylinder.radius * obj->cylinder.radius);
	quadratic_coefficients[W] = obj->cylinder.radius * obj->cylinder.radius;
	// float discriminant = quadratic_coefficients[Y] * quadratic_coefficients[Y] - 4.0F * quadratic_coefficients[X] * quadratic_coefficients[Z];
	if (compute_cylinder_intersection(ray.vec, oc, ca, &quadratic_coefficients))
		return false; // No intersection

	// Compute the roots of the quadratic
	float sqrt_discriminant = sqrtf(quadratic_coefficients[W]);


	float t0 = ((quadratic_coefficients[Y] * -1) - sqrt_discriminant) / (2.0F * quadratic_coefficients[X]);
	float t1 = ((quadratic_coefficients[Y] * -1) + sqrt_discriminant) / (2.0F * quadratic_coefficients[X]);

	// Step 4: Determine the valid intersection point
	if (t0 > t1) // Ensure t0 is the smaller value
	{
		float temp = t0;
		t0 = t1;
		t1 = temp;
	}

	// Check if the intersection is within the finite height of the cylinder
	// Adjust to grow symmetrically: height / 2 goes both up and down
	float y0 = vdot(ca, vadd(oc, vscale(ray.vec, t0)));
	float y1 = vdot(ca, vadd(oc, vscale(ray.vec, t1)));

	float valid_t = -1.0F;
	uint8_t hit_type = 0;

	// Ensure the intersection is within the cylinder's height bounds
	if (y0 >= -obj->cylinder.height / 2.0F && y0 <= obj->cylinder.height / 2.0F)
	{
		valid_t = t0;
		hit_type = CYL_BODY; // Cylinder body
	}
	else if (y1 >= -obj->cylinder.height / 2.0F && y1 <= obj->cylinder.height / 2.0F)
	{
		valid_t = t1;
		hit_type = CYL_BODY; // Cylinder body
	}

	// Step 5: Check caps if the body intersections are invalid
	t_vec4 top_cap = vadd(obj->coords, vscale(ca, obj->cylinder.height / 2.0F));
	t_vec4 bottom_cap = vsub(obj->coords, vscale(ca, obj->cylinder.height / 2.0F));

	float t_top, t_bottom;
	bool hit_top = intersect_cylinder_caps(ray.origin, ray.vec, top_cap, ca, &t_top);
	bool hit_bottom = intersect_cylinder_caps(ray.origin, ray.vec, bottom_cap, ca, &t_bottom);

	// Validate cap intersections
	if (hit_top)
	{
		t_vec4 p = vadd(ray.origin, vscale(ray.vec, t_top));
		if (vlen(vsub(p, top_cap)) <= obj->cylinder.radius)
		{
			if (valid_t < 0.0F || t_top < valid_t)
			{
				valid_t = t_top;
				hit_type = CYL_TOP; // Cylinder cap
			}
		}
	}

	if (hit_bottom)
	{
		t_vec4 p = vadd(ray.origin, vscale(ray.vec, t_bottom));
		if (vlen(vsub(p, bottom_cap)) <= obj->cylinder.radius)
		{
			if (valid_t < 0.0F || t_bottom < valid_t)
			{
				valid_t = t_bottom;
				hit_type = CYL_BOTTOM; // Cylinder cap
			}
		}
	}

	if (valid_t < 0.0F)
		return false;

	*t = valid_t;
	return hit_type;
}
