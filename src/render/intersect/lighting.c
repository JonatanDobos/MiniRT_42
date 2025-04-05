#include <scene.h>
#include <mathRT.h>
#include <render.h>

//	Static Functions
static bool	calc_hard_shadow(t_scene *sc, t_ray ray, t_vec4 light_dir, uint32_t light);
static float	calc_soft_shadow(t_scene *sc, t_ray ray, t_vec4 light_pos, uint32_t light);

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
		if (sc->soft_shadows == false || THREADS == 1 || sc->shadow_sample_gridsize < 2)
		{
			if (calc_hard_shadow(sc, (t_ray){point, normal}, light_dir, i))
				shadow = 0.1F;
			else
				shadow = 1.0F;
		}
		else
			shadow = calc_soft_shadow(sc, (t_ray){point, normal}, sc->lights[i].coords, i);
		diff = clamp(vdot(normal, light_dir), 0.0F, 1.0F) * sc->lights[i].l.brightness;
		result += (obj_color * sc->lights[i].color * bcast3(diff * shadow));
		++i;
	}
	return (vec_clamp(result, 0.0F, 1.0F));
}

static bool	calc_hard_shadow(t_scene *sc, t_ray ray, t_vec4 light_dir, uint32_t light)
{
	float		distance;
	t_vec4		origin;
	uint32_t	i;
	float		t;

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

//--------------- Soft shadows -----------------
// Work in progress.

t_vec4	rotate_2d(t_vec4 v, float angle)
{
	float cos_a = cosf(angle);
	float sin_a = sinf(angle);

	return ((t_vec4)
	{
		v[X] * cos_a - v[Y] * sin_a,
		v[X] * sin_a + v[Y] * cos_a,
		0.0F,
		0.0F
	});
}

t_vec4	grid_disk_sample(int idx, int grid_size, float angle)
{
	int x = idx % grid_size;
	int y = idx / grid_size;

	float fx = ((float)x + 0.5F) / grid_size * 2.0F - 1.0F;
	float fy = ((float)y + 0.5F) / grid_size * 2.0F - 1.0F;

	t_vec4 offset = (t_vec4){fx, fy, 0.0F, 0.0F};

	// Optional: discard points outside unit disk
	if (fx * fx + fy * fy > 1.0F)
		return (t_vec4){0.0F, 0.0F, 0.0F, 0.0F};

	return (rotate_2d(offset, angle));
}

t_vec4	get_disk_sample_pos(t_vec4 light_pos, int idx, int grid_size, float angle, float radius)
{
	t_vec4	offset = grid_disk_sample(idx, grid_size, angle);
	return vadd(light_pos, vscale(offset, radius));
}

bool	is_occluded(t_scene *sc, t_vec4 origin, t_vec4 dir, float max_dist)
{
	t_ray	ray = {vadd(origin, vscale(dir, SHADOW_EPSILON)), dir};
	float	t;

	for (uint32_t j = 0; j < sc->o_arr_size; j++)
	{
		if (ray_intersect_table(ray, &sc->objs[j], &t)
			&& t > SHADOW_EPSILON && t < max_dist)
			return true;
	}
	return false;
}

static float	calc_soft_shadow(t_scene *sc, t_ray ray, t_vec4 light_pos, uint32_t light)
{
	int				hit_count = 0;
	float			radius = sc->lights[light].l.radius;
	float			angle = 3.14159F * (light * 0.618F);
	float			distance = vlen(vsub(light_pos, ray.origin));
	const uint16_t	total_samples = sc->shadow_sample_gridsize * sc->shadow_sample_gridsize;

	for (int i = 0; i < total_samples; i++)
	{
		t_vec4 sample_pos = get_disk_sample_pos(light_pos, i, \
				sc->shadow_sample_gridsize, angle, radius);
		t_vec4 light_dir = vnorm(vsub(sample_pos, ray.origin));
		if (is_occluded(sc, ray.origin, light_dir, distance))
			hit_count++;
	}
	return 1.0F - ((float)hit_count / (float)total_samples);
}
