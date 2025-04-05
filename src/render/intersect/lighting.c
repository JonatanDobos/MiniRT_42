#include <scene.h>
#include <mathRT.h>
#include <render.h>

//	Static Functions
static bool	calc_shadow(t_scene *sc, t_ray ray, t_vec4 light_dir, uint32_t light);

t_objs	*render_light(t_scene *sc, t_ray ray, float *closest_t, t_objs *closest_obj)
{
	uint32_t	i;
	float		t;

	i = 0;
	while (i < sc->l_arr_size)
	{
		if (ray_intersect_sphere(ray, &sc->lights[i], &t) && t < *closest_t)
		{
			closest_obj = sc->lights + i;
			*closest_t = t;
		}
		++i;
	}
	return (closest_obj);
}

t_vec4	calc_lighting(t_scene *sc, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
{
	t_vec4			light_dir;
	t_vec4			result;
	float			shadow;
	float			diff;
	uint32_t		i;

	result = obj_color * sc->ambient.color * bcast3(sc->ambient.a.ratio);
	i = 0;
	while (i < sc->l_arr_size)
	{
		light_dir = vnorm(vsub(sc->lights[i].coords, point));
		if (calc_shadow(sc, (t_ray){point, normal}, light_dir, i))
			shadow = 0.1F;
		else
			shadow = 1.0F;
		diff = clamp(vdot(normal, light_dir), 0.0F, 1.0F) * sc->lights[i].l.brightness;
		result += (obj_color * sc->lights[i].color * bcast3(diff * shadow));
		++i;
	}
	return (vec_clamp(result, 0.0F, 1.0F));
}

static bool	calc_shadow(t_scene *sc, t_ray ray, t_vec4 light_dir, uint32_t light)
{
	float		distance;
	t_vec4		origin;
	uint32_t	i;
	float		t;
	// float		shadow;

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
