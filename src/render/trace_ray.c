#include <scene.h>
#include <mathRT.h>
#include <render.h>

uint8_t ray_intersect_table(t_ray ray, t_objs *obj, float *t)
{
	static uint8_t	(*intersect_obj[NUM_OBJ_TYPES])(t_ray, t_objs *, float *) = {
		ray_intersect_plane,
		ray_intersect_sphere,
		ray_intersect_cylinder
	};

	return (intersect_obj[obj->type](ray, obj, t));
}

t_vec4	trace_ray(t_scene *scene, t_ray ray)
{
	float t, closest_t = INFINITY;
	t_vec4 pixel_color = {0, 0, 0, 1.0};
	t_vec4 normal;
	t_objs	*obj_closest_vp;
	uint32_t i;
	uint8_t	intersect;

	obj_closest_vp = NULL;
	i = 0;
	while (i < scene->arr_size)
	{
		intersect = ray_intersect_table(ray, scene->objs + i, &t);
		if (intersect && t < closest_t)
		{
			obj_closest_vp = scene->objs + i;
			closest_t = t;
			pixel_color = scene->objs[i].color;
			if (scene->objs[i].type == PLANE)
			{
				normal = scene->objs[i].plane.orientation;
			}
			else if (scene->objs[i].type == SPHERE)
			{
				normal = vnorm(vsub(vadd(ray.origin, vscale(ray.vec, t)), scene->objs[i].coords));




			}
			else if (scene->objs[i].type == CYLINDER)
			{
				if (intersect == 1)
				{
					t_vec4 hit_point = vadd(ray.origin, vscale(ray.vec, t));
					normal = vnorm(vsub(hit_point, vadd(scene->objs[i].coords, vscale(scene->objs[i].cylinder.orientation, \
						vdot(vsub(hit_point, scene->objs[i].coords), scene->objs[i].cylinder.orientation)))));
				}
				else if (intersect == 2)
					normal = vnorm(scene->objs[i].cylinder.orientation);
				else
					normal = vneg(vnorm(scene->objs[i].cylinder.orientation));
			}
		}
		++i;
	}

	// Apply lighting if an object was hit
	if (closest_t < INFINITY)
	{
		t_vec4 hit_point = vadd(ray.origin, vscale(ray.vec, closest_t));
		return (calculate_lighting(scene, hit_point, normal, pixel_color));
	}
	return (pixel_color); // Background color
}
