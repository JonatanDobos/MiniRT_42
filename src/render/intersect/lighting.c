#include <scene.h>
#include <mathRT.h>
#include <render.h>

t_vec4	calc_lighting(t_scene *sc, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
{
	t_vec4			result;
	t_vec4			light_dir;
	float			diff;
	uint32_t		i;
	float			shadow;

	// Ambient lighting
	result = obj_color * sc->ambient.color * bcast3(sc->ambient.a.ratio);
	
	i = 0;
	while (i < sc->l_arr_size)
	{
		// Diffuse lighting
		light_dir = vnorm(vsub(sc->lights[i].coords, point));

		// Get shadow factor (0.1 for shadowed, 1.0 for fully lit)
		shadow = calc_shadow(sc, (t_ray){point, normal}, light_dir, i) ? 0.1F : 1.0F;

		diff = clamp(vdot(normal, light_dir), 0.0F, 1.0F) * sc->lights[i].l.brightness;

		// **Apply per-light shadowing instead of returning early**
		result += (obj_color * sc->lights[i].color * bcast3(diff * shadow));

		++i;
	}
	return (vec_clamp(result, 0.0F, 1.0F));
}


// Hard shadow calculation.
bool	calc_shadow(t_scene *sc, t_ray ray, t_vec4 light_dir, uint32_t light)
{
	t_vec4		origin;
	// float		shadow;
	uint32_t	i;
	float		t;
	float		distance;

	i = 0;
	t = 0.0F;
	origin = vadd(ray.origin, vscale(light_dir, SHADOW_EPSILON));
	distance = vlen(vsub(sc->lights[light].coords, ray.origin));
	if (vdot(ray.vec, light_dir) < 0.0F)
		return (true);
	while (i < sc->o_arr_size)
	{
		if (ray_intersect_table((t_ray){origin, light_dir}, &sc->objs[i], &t)
			&& t > SHADOW_EPSILON && t < distance)
			return (true);
		++i;
	}
	return (false);
}

// Ray-sphere intersection
uint8_t	ray_intersect_light(t_ray ray, t_objs *obj, float *t)
{
	t_vec4	oc = vsub(ray.origin, obj->coords);
	float	a = vdot(ray.vec, ray.vec);
	float	b = 2.0F * vdot(oc, ray.vec);
	float	c = vdot(oc, oc) - obj->l.radius * obj->l.radius;
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

t_objs	*render_light(t_scene *sc, t_ray ray, float *closest_t, t_objs *closest_obj)
{
	uint32_t	i;
	float		t;

	i = 0;
	while (i < sc->l_arr_size)
	{
		if (ray_intersect_light(ray, &sc->lights[i], &t) && t < *closest_t)
		{
			closest_obj = sc->lights + i;
			*closest_t = t;
		}
		++i;
	}
	return (closest_obj);
}
