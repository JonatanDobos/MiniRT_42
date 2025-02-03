#include <scene.h>
#include <mathRT.h>

// Ray-plane intersection
uint8_t	ray_intersect_plane(t_ray ray, t_objs *obj, float *t)
{
	const float	denom = vdot(ray.vec, obj->plane.orientation);
	t_vec4		diff;

	if (fabs(denom) > EPSILON)
	{
		diff = vsub(obj->coords, ray.origin);
		*t = vdot(diff, obj->plane.orientation) / denom;
		return (*t >= 0);
	}
	return false;
}

// Ray-sphere intersection
uint8_t	ray_intersect_sphere(t_ray ray, t_objs *obj, float *t)
{
	t_vec4	oc = vsub(ray.origin, obj->coords);
	float	a = vdot(ray.vec, ray.vec);
	float	b = 2.0f * vdot(oc, ray.vec);
	float	c = vdot(oc, oc) - obj->sphere.radius * obj->sphere.radius;
	float	discriminant = b * b - 4 * a * c;
	float	sqrt_d;

	if (discriminant < 0)
		return (false);
	sqrt_d = sqrtf(discriminant);
	*t = (-b - sqrt_d) / (2.0f * a);
	if (*t < 0)
		*t = (-b + sqrt_d) / (2.0f * a);
	return (*t >= 0);
}
