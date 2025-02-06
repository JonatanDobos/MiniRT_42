#include <utils.h>
#include <scene.h>
#include <mathRT.h>
#include <render.h>

// Lighting calculation (ambient + diffuse)
t_vec4	calc_lighting(t_scene *sc, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
{
	t_vec4			result;
	t_vec4			light_dir;
	float			diff;
	uint32_t		i;

	// Ambient lighting
	result = obj_color * sc->ambient.color * bcast3(sc->ambient.a.ratio);
	i = 0;
	while (i < sc->l_arr_size)
	{
		// Diffuse lighting
		light_dir = vnorm(vsub(sc->lights[i].coords, point));
		if (calc_shadow(sc, (t_ray){point, normal}, light_dir, i) == true)
			return (result);
		diff = clamp(vdot(normal, light_dir), 0.0F, 1.0F) * sc->lights[i].l.brightness;

		result += (obj_color * sc->lights[i].color * bcast3(diff));
		++i;
	}
	return (vec_clamp(result, 0.0F, 1.0F));
}

// Hard shadow calculation.
bool	calc_shadow(t_scene *sc, t_ray ray, t_vec4 light_dir, uint32_t light)
{
	t_vec4		origin;
	float		shadow;
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

// // Lighting calculation (ambient + diffuse)
// t_vec4	calc_lighting(t_scene *sc, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
// {
// 	const t_vec4	scalar_amb = bcast3(sc->ambient.a.ratio);
// 	t_vec4			scalar_light;
// 	t_vec4			result;
// 	t_vec4			light_dir;
// 	float			diff;

// 	// Ambient lighting
// 	result = obj_color * sc->ambient.color * scalar_amb;

// 	// Diffuse lighting
// 	light_dir = vnorm(vsub(sc->light.coords, point));
// 	if (calc_shadow(sc, point, normal, light_dir) == true)
// 		return (result);
// 	diff = clamp(vdot(normal, light_dir), 0.0F, 1.0F) * sc->light.l.brightness;

// 	scalar_light = bcast3(diff);
// 	result += (obj_color * sc->light.color * scalar_light);
// 	return (vec_clamp(result, 0.0F, 1.0F));
// }

// // Hard shadow calculation.
// bool	calc_shadow(t_scene *sc, t_vec4 point, t_vec4 normal, t_vec4 light_dir)
// {
// 	t_vec4		origin;
// 	float		shadow;
// 	uint32_t	i;
// 	float		t;
// 	float		distance;

// 	i = 0;
// 	t = 0.0F;
// 	origin = vadd(point, vscale(light_dir, SHADOW_EPSILON));
// 	distance = vlen(vsub(sc->light.coords, point));
// 	if (vdot(normal, light_dir) < 0.0F)
// 		return (true);
// 	while (i < sc->o_arr_size)
// 	{
// 		if (ray_intersect_table((t_ray){origin, light_dir}, &sc->objs[i], &t)
// 			&& t > SHADOW_EPSILON && t < distance)
// 			return (true);
// 		++i;
// 	}
// 	return (false);
// }
