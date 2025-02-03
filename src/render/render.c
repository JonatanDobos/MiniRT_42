#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>
#include <RTmlx.h>
#include <sys/param.h>
#include <mathRT.h>
#include <render.h>

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

t_vec4	transform_ray_dir(t_vec4 ndc_dir, t_vec4 cam_orient)
{
	// Normalize the camera orientation vector (forward direction)
	t_vec4	z_axis = vnorm(cam_orient);

	// Create an "up" vector (default is Y-axis in world space)
	t_vec4	up = {0, 1, 0};
	if (fabsf(z_axis[X]) == 0.0f && fabsf(z_axis[Z]) == 0.0f) // Handle edge case where cam_orient is vertical
		up = (z_axis[Y] > 0) ? (t_vec4){0, 0, -1} : (t_vec4){0, 0, 1};

	// Calculate the right vector (x-axis of the camera)
	t_vec4	x_axis = vnorm(vcross(up, z_axis));

	// Calculate the up vector (y-axis of the camera, perpendicular to both)
	t_vec4	y_axis = vcross(z_axis, x_axis);

	// Apply the rotation matrix to the direction vector
	t_vec4 world_dir = {
		x_axis[X] * ndc_dir[X] + y_axis[X] * ndc_dir[Y] + z_axis[X] * ndc_dir[Z],
		x_axis[Y] * ndc_dir[X] + y_axis[Y] * ndc_dir[Y] + z_axis[Y] * ndc_dir[Z],
		x_axis[Z] * ndc_dir[X] + y_axis[Z] * ndc_dir[Y] + z_axis[Z] * ndc_dir[Z]
	};
	return vnorm(world_dir);
}

// Render the scene
void	render(t_rt *rt)
{
	uint16_t	y;
	uint16_t	x;
	t_ray		ray;
	float		ndc_x;
	float		ndc_y;

	y = 0;
	while (y < rt->win->rndr_hght)
	{
		x = 0;
		while (x < rt->win->rndr_wdth)
		{
			ndc_x = (2 * ((x + 0.5f) / (float)rt->win->rndr_wdth) - 1) * rt->win->aspectrat;
			ndc_y = 1 - 2 * ((y + 0.5f) / (float)rt->win->rndr_hght);
			ray.origin = rt->scene->camera.coords;
			ray.vec = transform_ray_dir((t_vec4){ndc_x, ndc_y, rt->scene->camera.c.zvp_dist, 0}, rt->scene->camera.c.orientation);
			scaled_res_set_pixel(rt->win, x, y, trace_ray(rt->scene, ray));
			++x;
		}
		++y;
	}
}
