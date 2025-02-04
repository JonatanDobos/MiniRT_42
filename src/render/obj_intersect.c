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
		return (*t >= 0.0F);
	}
	return false;
}

// Ray-sphere intersection
uint8_t	ray_intersect_sphere(t_ray ray, t_objs *obj, float *t)
{
	t_vec4	oc = vsub(ray.origin, obj->coords);
	float	a = vdot(ray.vec, ray.vec);
	float	b = 2.0F * vdot(oc, ray.vec);
	float	c = vdot(oc, oc) - obj->sphere.radius * obj->sphere.radius;
	float	discriminant = b * b - 4.0F * a * c;
	float	sqrt_d;

	if (discriminant < 0.0F)
		return (false);
	sqrt_d = sqrtf(discriminant);
	*t = (-b - sqrt_d) / (2.0F * a);
	if (*t < 0.0F)
		*t = (-b + sqrt_d) / (2.0F * a);
	return (*t >= 0.0F);
}
