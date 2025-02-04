#include <utils.h>
#include <scene.h>
#include <mathRT.h>
#include <render.h>

// Lighting calculation (ambient + diffuse)
t_vec4	calc_lighting(t_scene *sc, t_vec4 point, t_vec4 normal, t_vec4 obj_color)
{
	const t_vec4	scalar_amb = bcast3(sc->ambient.a.ratio);
	t_vec4			scalar_light;
	t_vec4			result;
	t_vec4			light_dir;
	float			diff;

	// Ambient lighting
	result = obj_color * sc->ambient.color * scalar_amb;

	// Diffuse lighting
	light_dir = vnorm(vsub(sc->light.coords, point));
	diff = clamp(vdot(normal, light_dir), 0.0F, 1.0F) * sc->light.l.brightness;

	scalar_light = bcast3(diff);
	result += (obj_color * sc->light.color * scalar_light);

	// Shadow calculation
	result *= calc_shadow(sc, point, light_dir);
	return (vec_clamp(result, 0.0F, 1.0F));
}

t_vec4	calc_shadow(t_scene *sc, t_vec4 point, t_vec4 light_dir)
{
	t_vec4		origin;
	float		shadow;
	uint32_t	i;
	float		t;
	float		distance;

	i = 0;
	t = 0.0F;
	origin = vadd(point, vscale(light_dir, SHADOW_EPSILON));
	distance = vlen(vsub(sc->light.coords, point));
	while (i < sc->arr_size)
	{
		if (ray_intersect_table((t_ray){origin, light_dir}, &sc->objs[i], &t)
			&& t > SHADOW_EPSILON && t < distance)
			return (bcast3(0.1F));
		++i;
	}
	return (bcast3(1.0F));
}
