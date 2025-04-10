#include <scene.h>
#include <mathRT.h>
#include <render.h>

// Returns the point along the ray at parameter t.
static inline t_vec4 ray_at(t_ray ray, float t)
{
	return (vadd(ray.origin, vscale(ray.vec, t)));
}

// Solves the quadratic equation: a*t^2 + b*t + c = 0.
// Returns true if real solutions exist and assigns *t0 and *t1 (ensuring *t0 <= *t1).
static bool solve_quadratic(const float a, const float b, const float c, float *t0, float *t1)
{
	const float	disc = b * b - 4.0F * a * c;
	float		sqrt_disc;
	float		tmp;

	if (disc < 0.0F)
		return (false);
	sqrt_disc = sqrtf(disc);
	*t0 = (-b - sqrt_disc) / (2.0F * a);
	*t1 = (-b + sqrt_disc) / (2.0F * a);
	if (*t0 > *t1)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
	return (true);
}

// Computes the intersection of a ray and a plane (for caps).
static bool intersect_cylinder_caps(t_vec4 origin, t_vec4 dir, t_vec4 plane_point, t_vec4 plane_normal, float *t)
{
	const float	denom = vdot(plane_normal, dir);
	t_vec4		origin_to_plane;

	if (fabs(denom) > 1e-6F)
	{
		origin_to_plane = vsub(plane_point, origin);
		*t = vdot(origin_to_plane, plane_normal) / denom;
		return (*t >= 0.0F);
	}
	return (false);
}

// Checks whether the hit on a cap is within its circular boundary.
static bool is_cap_hit_valid(t_ray ray, t_vec4 cap_center, float cap_radius, float t_val)
{
	const t_vec4	p = ray_at(ray, t_val);
	const t_vec4	d = vsub(p, cap_center);

	return (vdot(d, d) <= cap_radius * cap_radius);
}

// Checks if one of the body intersections is valid (i.e. within the cylinder's finite height).
static uint8_t check_body_intersection(t_ray ray, t_objs *obj, t_vec4 ca,
	float t0, float t1, float half_height, float *valid_t)
{
	const t_vec4	hit0 = ray_at(ray, t0);
	const t_vec4	hit1 = ray_at(ray, t1);
	const float		y0 = vdot(vsub(hit0, obj->coords), ca);
	const float		y1 = vdot(vsub(hit1, obj->coords), ca);

	if (y0 >= -half_height && y0 <= half_height)
	{
		*valid_t = t0;
		return (CYL_BODY);
	}
	else if (y1 >= -half_height && y1 <= half_height)
	{
		*valid_t = t1;
		return (CYL_BODY);
	}
	return (CYL_NONE);
}

// Checks the intersection with one cylinder cap and updates t_hit if valid.
static uint8_t get_cap_intersection(t_ray ray, t_vec4 cap_center, t_vec4 ca,
	float cap_radius, uint8_t cap_type, float *t_hit)
{
	float	t_cap;

	if (intersect_cylinder_caps(ray.origin, ray.vec, cap_center, ca, &t_cap))
	{
		if (is_cap_hit_valid(ray, cap_center, cap_radius, t_cap))
		{
			*t_hit = t_cap;
			return cap_type;
		}
	}
	return (CYL_NONE);
}

// Needs to be further split up!
uint8_t ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t)
{
	// Normalize the cylinder axis.
	const t_vec4	ca = vnorm(obj->cylinder.orientation);
	const t_vec4	oc = vsub(ray.origin, obj->coords);
	
	// Project ray direction and offset vector onto plane perpendicular to the axis.
	const t_vec4	rd = vsub(ray.vec, vscale(ca, vdot(ray.vec, ca)));
	const t_vec4	oc_proj = vsub(oc, vscale(ca, vdot(oc, ca)));
	
	// Solve quadratic for body intersections.
	float t0, t1;
	if (!solve_quadratic(vdot(rd, rd), 2.0F * vdot(rd, oc_proj), \
		vdot(oc_proj, oc_proj) - obj->cylinder.radius * obj->cylinder.radius, &t0, &t1))
		return (CYL_NONE);
	if (t1 < 0.0F)
		return (CYL_NONE);
	if (t0 < 0.0F)
		t0 = t1;
	
	float half_height = obj->cylinder.height / 2.0F;
	float valid_t = -1.0F;
	uint8_t hit_type = CYL_NONE;
	
	// Check for valid body intersection.
	hit_type = check_body_intersection(ray, obj, ca, t0, t1, half_height, &valid_t);
	
	// Determine cap centers.
	t_vec4 top_cap = vadd(obj->coords, vscale(ca, half_height));
	t_vec4 bottom_cap = vsub(obj->coords, vscale(ca, half_height));
	
	// Check cap intersections.
	float t_cap;
	uint8_t cap_hit = get_cap_intersection(ray, top_cap, ca, obj->cylinder.radius, CYL_TOP, &t_cap);
	if (cap_hit != CYL_NONE && (valid_t < 0.0F || t_cap < valid_t))
	{
		valid_t = t_cap;
		hit_type = cap_hit;
	}
	cap_hit = get_cap_intersection(ray, bottom_cap, ca, obj->cylinder.radius, CYL_BOTTOM, &t_cap);
	if (cap_hit != CYL_NONE && (valid_t < 0.0F || t_cap < valid_t))
	{
		valid_t = t_cap;
		hit_type = cap_hit;
	}
	
	if (valid_t < 0.0F)
		return CYL_NONE;
	*t = valid_t;
	return hit_type;
}
