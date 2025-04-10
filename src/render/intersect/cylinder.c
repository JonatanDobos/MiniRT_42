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
	return (false);
}

// static bool compute_cylinder_intersection(t_vec4 ray_vec, t_vec4 oc, t_vec4 ca, t_vec4 *quad_coeffs)
// {
// 	// Step 2: Project ray direction and oc onto plane perpendicular to the cylinder axis
// 	t_vec4 rd = vsub(ray_vec, vscale(ca, vdot(ray_vec, ca))); // Projected ray direction
// 	t_vec4 oc_proj = vsub(oc, vscale(ca, vdot(oc, ca)));     // Projected oc

// 	// Step 3: Solve quadratic equation for the intersection
// 	(*quad_coeffs)[X] = vdot(rd, rd); // a
// 	(*quad_coeffs)[Y] = 2.0F * vdot(rd, oc_proj); // b
// 	(*quad_coeffs)[Z] = vdot(oc_proj, oc_proj) - (*quad_coeffs)[W]; // c
// 	(*quad_coeffs)[W] = (*quad_coeffs)[Y] * (*quad_coeffs)[Y] - 4.0F * (*quad_coeffs)[X] * (*quad_coeffs)[Z];

// 	if ((*quad_coeffs)[W] < 0.0F)
// 		return (false);
// 	(*quad_coeffs)[W] = sqrtf((*quad_coeffs)[W]);
// 	return (true); // Return true if there is an intersection
// }

static bool compute_cylinder_intersection(t_vec4 ray_vec, t_vec4 oc, t_vec4 ca, float *t)
{
	const t_vec4	rd = vsub(ray_vec, vscale(ca, vdot(ray_vec, ca)));
	const t_vec4	oc_proj = vsub(oc, vscale(ca, vdot(oc, ca)));
	t_vec4			quadratic_coefficients;
	float			discriminant;
	float			tmp;

	quadratic_coefficients[X] = vdot(rd, rd); // a
	quadratic_coefficients[Y] = 2.0F * vdot(rd, oc_proj); // b
	quadratic_coefficients[Z] = vdot(oc_proj, oc_proj) - t[2]; // c
	discriminant = (quadratic_coefficients[Y] * quadratic_coefficients[Y]) - \
	(4.0F * (quadratic_coefficients[X] * quadratic_coefficients[Z]));
	if (discriminant < 0.0F)
		return (false);
	discriminant = sqrtf(discriminant);
	t[0] = (-quadratic_coefficients[Y] - discriminant) / (2.0F * quadratic_coefficients[X]);
	t[1] = (-quadratic_coefficients[Y] + discriminant) / (2.0F * quadratic_coefficients[X]);
	if (t[0] > t[1])
	{
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
	return (true);
}


static uint8_t validate_cap_intersection(t_ray ray, t_objs *obj, t_vec4 ca, float *t_tmp)
{
	const t_vec4	top_cap = vadd(obj->coords, vscale(ca, obj->cylinder.height / 2.0F));
	const t_vec4	bottom_cap = vsub(obj->coords, vscale(ca, obj->cylinder.height / 2.0F));
	const bool		hit_top = intersect_cylinder_caps(ray.origin, ray.vec, top_cap, ca, &t_tmp[0]);
	const bool		hit_bottom = intersect_cylinder_caps(ray.origin, ray.vec, bottom_cap, ca, &t_tmp[1]);
	uint8_t			hit_type;

	hit_type = 0;
	if (hit_top)
	{
		t_vec4 p = vadd(ray.origin, vscale(ray.vec, t_tmp[0]));
		if (vlen(vsub(p, top_cap)) <= obj->cylinder.radius)
		{
			if (t_tmp[2] < 0.0F || t_tmp[0] < t_tmp[2])
			{
				t_tmp[2] = t_tmp[0];
				hit_type = CYL_TOP;
			}
		}
	}
	if (hit_bottom)
	{
		t_vec4 p = vadd(ray.origin, vscale(ray.vec, t_tmp[1]));
		if (vlen(vsub(p, bottom_cap)) <= obj->cylinder.radius)
		{
			if (t_tmp[2] < 0.0F || t_tmp[1] < t_tmp[2])
			{
				t_tmp[2] = t_tmp[1];
				hit_type = CYL_BOTTOM;
			}
		}
	}
	return (hit_type);
}

uint8_t ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t)
{
	t_vec4	oc = vsub(ray.origin, obj->coords);
	t_vec4	ca = vnorm(obj->cylinder.orientation);
	float	t_tmp[3];
	uint8_t hit_type[2];

	t_tmp[2] = obj->cylinder.radius * obj->cylinder.radius;
	if (compute_cylinder_intersection(ray.vec, oc, ca, t_tmp) == false)
		return (false);

	t_tmp[2] = -1.0F;
	hit_type[0] = 0;
	float y0 = vdot(ca, vadd(oc, vscale(ray.vec, t_tmp[0])));
	float y1 = vdot(ca, vadd(oc, vscale(ray.vec, t_tmp[1])));
	if (y0 >= -obj->cylinder.height / 2.0F && y0 <= obj->cylinder.height / 2.0F)
	{
		t_tmp[2] = t_tmp[0];
		hit_type[0] = CYL_BODY;
	}
	else if (y1 >= -obj->cylinder.height / 2.0F && y1 <= obj->cylinder.height / 2.0F)
	{
		t_tmp[2] = t_tmp[1];
		hit_type[0] = CYL_BODY;
	}
	hit_type[1] = validate_cap_intersection(ray, obj, ca, t_tmp);
	if (hit_type[1] != 0)
        hit_type[0] = hit_type[1];
	if (t_tmp[2] < 0.0F)
		return (false);
	*t = t_tmp[2];
	return hit_type[0];
}
