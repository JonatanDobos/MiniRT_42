#include <scene.h>
#include <mathRT.h>
#include <render.h>

// Returns the point along the ray at parameter t.
t_vec4	ray_at(t_ray ray, float t)
{
	return (vadd(ray.origin, vscale(ray.vec, t)));
}

// Solves the quadratic equation: a*t^2 + b*t + c = 0.
// Returns true if real solutions exist and assigns *t0 and *t1 (ensuring *t0 <= *t1).
static bool	solve_quadratic(const float a, const float b, const float c, t_cyl *cy)
{
	const float	disc = b * b - 4.0F * a * c;
	float		sqrt_disc;
	float		tmp;

	if (disc < 0.0F)
		return (false);
	sqrt_disc = sqrtf(disc);
	cy->t[0] = (-b - sqrt_disc) / (2.0F * a);
	cy->t[1] = (-b + sqrt_disc) / (2.0F * a);
	if (cy->t[0] > cy->t[1])
	{
		tmp = cy->t[0];
		cy->t[0] = cy->t[1];
		cy->t[1] = tmp;
	}
	return (true);
}

// Computes the intersection of a ray and a plane (for caps).
static bool	intersect_cylinder_caps(t_ray ray, t_ray plane, float *t)
{
	const float	denom = vdot(plane.vec, ray.vec);
	t_vec4		origin_to_plane;

	if (fabs(denom) > 1e-6F)
	{
		origin_to_plane = vsub(plane.origin, ray.origin);
		*t = vdot(origin_to_plane, plane.vec) / denom;
		return (*t >= 0.0F);
	}
	return (false);
}

// Checks whether the hit on a cap is within its circular boundary.
static bool	is_cap_hit_valid(t_ray ray, t_vec4 cap_center, float cap_radius, float t_val)
{
	const t_vec4	p = ray_at(ray, t_val);
	const t_vec4	d = vsub(p, cap_center);

	return (vdot(d, d) <= cap_radius * cap_radius);
}

// Checks if one of the body intersections is valid (i.e. within the cylinder's finite height).
static uint8_t	check_body_intersection(t_ray ray, t_objs *obj, t_cyl *cy)
{
	const t_vec4	hit0 = ray_at(ray, cy->t[0]);
	const t_vec4	hit1 = ray_at(ray, cy->t[1]);
	const float		y0 = vdot(vsub(hit0, obj->coords), cy->ca);
	const float		y1 = vdot(vsub(hit1, obj->coords), cy->ca);

	if (y0 >= -cy->half_height && y0 <= cy->half_height)
	{
		cy->valid_t = cy->t[0];
		return (CYL_BODY);
	}
	else if (y1 >= -cy->half_height && y1 <= cy->half_height)
	{
		cy->valid_t = cy->t[1];
		return (CYL_BODY);
	}
	return (CYL_NONE);
}

// Checks the intersection with one cylinder cap and updates t_hit if valid.
static uint8_t	get_cap_intersection(t_cyl_cap *cycap, t_ray ray, t_vec4 ca, uint8_t cap_type)
{
	float	t_cap;
	t_vec4	center;

	if (cap_type == CYL_TOP)
		center = cycap->top_cap;
	else
		center = cycap->bottom_cap;
	if (intersect_cylinder_caps(ray, (t_ray){center, ca}, &t_cap))
	{
		if (is_cap_hit_valid(ray, center, cycap->cap_radius, t_cap))
		{
			cycap->t_cap = t_cap;
			return cap_type;
		}
	}
	return (CYL_NONE);
}

uint8_t	check_cyl_caps(t_cyl *cy, t_ray ray, t_objs *obj, uint8_t hit_type)
{
	t_cyl_cap	cycap;
	uint8_t		cap_hit;

	cycap.top_cap = vadd(obj->coords, vscale(cy->ca, cy->half_height));
	cycap.bottom_cap = vsub(obj->coords, vscale(cy->ca, cy->half_height));
	cycap.cap_radius = obj->cylinder.radius;
	cap_hit = get_cap_intersection(&cycap, ray, cy->ca, CYL_TOP);
	if (cap_hit != CYL_NONE && (cy->valid_t < 0.0F || cycap.t_cap < cy->valid_t))
	{
		cy->valid_t = cycap.t_cap;
		hit_type = cap_hit;
	}
	cap_hit = get_cap_intersection(&cycap, ray, cy->ca, CYL_BOTTOM);
	if (cap_hit != CYL_NONE && (cy->valid_t < 0.0F || cycap.t_cap < cy->valid_t))
	{
		cy->valid_t = cycap.t_cap;
		hit_type = cap_hit;
	}
	return (hit_type);
}

uint8_t	ray_intersect_cylinder(t_ray ray, t_objs *obj, float *t)
{
	t_cyl	cy;
	uint8_t	hit_type;

	cy.ca = vnorm(obj->cylinder.orientation);
	cy.oc = vsub(ray.origin, obj->coords);
	cy.rd = vsub(ray.vec, vscale(cy.ca, vdot(ray.vec, cy.ca)));
	cy.oc_proj = vsub(cy.oc, vscale(cy.ca, vdot(cy.oc, cy.ca)));
	cy.half_height = obj->cylinder.height / 2.0F;
	cy.valid_t = -1.0F;
	if (!solve_quadratic(vdot(cy.rd, cy.rd), 2.0F * vdot(cy.rd, cy.oc_proj), \
		vdot(cy.oc_proj, cy.oc_proj) - obj->cylinder.radius * obj->cylinder.radius, &cy))
		return (CYL_NONE);
	if (cy.t[1] < 0.0F)
		return (CYL_NONE);
	if (cy.t[0] < 0.0F)
		cy.t[0] = cy.t[1];
	hit_type = CYL_NONE;
	hit_type = check_body_intersection(ray, obj, &cy);
	hit_type = check_cyl_caps(&cy, ray, obj, hit_type);
	if (cy.valid_t < 0.0F)
		return (CYL_NONE);
	*t = cy.valid_t;
	return (hit_type);
}
