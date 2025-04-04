#include <scene.h>
#include <mathRT.h>
#include <render.h>

uint8_t	ray_intersect_table(t_ray ray, t_objs *obj, float *t)
{
	static uint8_t	(*intersect_obj[NUM_OBJ_TYPES])(t_ray, t_objs *, float *) = {
		ray_intersect_plane,
		ray_intersect_sphere,
		ray_intersect_cylinder
	};

	return (intersect_obj[obj->type](ray, obj, t));
}

t_vec4 calculate_normal_cylinder(t_objs *obj, t_ray ray, float t, uint8_t intersect_type)
{
	t_vec4	hit_point = vadd(ray.origin, vscale(ray.vec, t));
	t_vec4	normal;

	if (intersect_type == CYL_BODY)
	{
		normal = vsub(hit_point, 
				vadd(obj->coords, 
				vscale(obj->cylinder.orientation, 
				vdot(vsub(hit_point, obj->coords), obj->cylinder.orientation))));
		
		normal = vnorm(normal);

		// **Ensure normal is correctly oriented**?????
		if (vdot(normal, ray.vec) > 0.0F)
			normal = vscale(normal, -1.0F);
		return (normal);
	} 
	else if (intersect_type == CYL_TOP)
	{
		return (vnorm(obj->cylinder.orientation));
	}
	else
	{
		return (vnorm(obj->cylinder.orientation) * -1);
	}
}

uint32_t	find_closest_object(t_scene *sc, t_ray ray, float *closest_t, uint8_t *closest_intersect_type)
{
	uint32_t	closest_obj;
	uint32_t	i;
	float		t;
	uint8_t		intersect_type;

	closest_obj = 0;
	i = 0;
	*closest_t = INFINITY;
	*closest_intersect_type = 0;
	while (i < sc->o_arr_size)
	{
		intersect_type = ray_intersect_table(ray, sc->objs + i, &t);
		if (intersect_type && t < *closest_t)
		{
			closest_obj = i;
			*closest_t = t;
			*closest_intersect_type = intersect_type;
		}
		++i;
	}
	return (closest_obj);
}

t_vec4 calculate_normal(t_objs *obj, t_ray *ray, float t, uint8_t intersect_type)
{
	if (obj->type == PLANE)
	{
		return (obj->plane.orientation);
	}
	if (obj->type == SPHERE)
	{
		return (vnorm(vsub(vadd(ray->origin, vscale(ray->vec, t)), obj->coords)));
	}
	if (obj->type == CYLINDER)
	{
		return (calculate_normal_cylinder(obj, *ray, t, intersect_type));
	}
	return (t_vec4){0.0F, 0.0F, 0.0F, 1.0F};
}

t_vec4 trace_ray(t_scene *sc, t_ray ray)
{
	float	closest_t;
	uint8_t	closest_intersect_type;
	t_vec4	pixel_color;
	t_objs	*closest_obj;
	t_vec4	hit_point;

	pixel_color = (t_vec4){0.0F, 0.0F, 0.0F, 1.0F};
	closest_obj = sc->objs + find_closest_object(sc, ray, &closest_t, &closest_intersect_type);
	if (sc->intersect_lights == true)
		closest_obj = render_light(sc, ray, &closest_t, closest_obj);
	if (closest_t < INFINITY && closest_t > 0.0F)
	{
		pixel_color = closest_obj->color;
		if (closest_obj->type == LIGHT)
			return (pixel_color);
		hit_point = vadd(ray.origin, vscale(ray.vec, closest_t));
		return (calc_lighting(sc, hit_point,
				calculate_normal(closest_obj, &ray, closest_t,
				closest_intersect_type), pixel_color));
	}
	return (pixel_color);
}
