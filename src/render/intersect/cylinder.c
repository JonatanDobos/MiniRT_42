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

uint8_t ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t)
{
	// Step 1: Compute vectors for the cylinder's axis
	t_vec4 ca = vnorm(obj->cylinder.orientation); // Cylinder axis (normalized)
	t_vec4 oc = vsub(ray.origin, obj->coords); // Vector from ray origin to obj->cylinder center
	
	// Step 2: Project ray direction and oc onto plane perpendicular to the cylinder axis
	t_vec4 rd = vsub(ray.vec, vscale(ca, vdot(ray.vec, ca))); // Projected ray direction
	t_vec4 oc_proj = vsub(oc, vscale(ca, vdot(oc, ca)));     // Projected oc

	// Step 3: Solve quadratic equation for the intersection
	float a = vdot(rd, rd);
	float b = 2.0F * vdot(rd, oc_proj);
	float c = vdot(oc_proj, oc_proj) - (obj->cylinder.radius * obj->cylinder.radius);
	float discriminant = b * b - 4.0F * a * c;
	if (discriminant < 0.0F)
		return false; // No intersection

	// Compute the roots of the quadratic
	float sqrt_discriminant = sqrtf(discriminant);
	float t0 = (-b - sqrt_discriminant) / (2.0F * a);
	float t1 = (-b + sqrt_discriminant) / (2.0F * a);

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
