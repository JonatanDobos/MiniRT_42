#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>
#include <RTmlx.h>

float	intersect_plane(t_objs *obj, t_cvec4 ray_position, t_cvec4 orientation)
{
	t_cfloat	denom = dot_product(obj->plane.direction, orientation);
	t_cvec4		ray_to_plane_vector = obj->coords - ray_position;
	float		intersection_distance;

	if (fabsf(denom) > 1e-6F) {
		intersection_distance = dot_product(ray_to_plane_vector, obj->plane.direction) / denom;
		if (intersection_distance >= 0.0F) {
			return (intersection_distance);
		}
	}
	return (-1.0F);
}

float	intersect_sphere(t_objs *obj, t_cvec4 ray_position, t_cvec4 orientation)
{
	t_cvec4		oc = ray_position - obj->coords;
	t_cfloat	a = dot_product(orientation, orientation);
	t_cfloat	b = 2.0F * dot_product(oc, orientation);
	t_cfloat	c = dot_product(oc, oc) - obj->sphere.radius * obj->sphere.radius;
	t_cfloat	discriminant = b * b - 4.0F * a * c;

	if (discriminant > 0.0F)
	{
		float t0 = (-b - fast_sqrt(discriminant)) / (2.0F * a);
		float t1 = (-b + fast_sqrt(discriminant)) / (2.0F * a);
		if (t0 > 0.0F && t1 > 0.0F)
		{
			return ((t0 < t1) ? t0 : t1); // Choose the closest positive t value
		}
	}
	return (-1.0F);
}

// Function to check if the intersection point is within the height of the cylinder
bool	check_height(const t_objs *obj, const t_cylinder *cyl, t_cvec4 ray_position, t_cvec4 orientation, float t)
{
	t_cvec4		intersection_point = ray_position + orientation * t;
	t_cvec4		base_to_intersection = intersection_point - obj->coords;
	t_cfloat	height = dot_product(base_to_intersection, normalize(cyl->direction));

	return (height >= 0.0F && height <= cyl->height);
}

float	intersect_cylinder(t_objs *obj, t_cvec4 ray_position, t_cvec4 orientation)
{
	t_cylinder	*cylinder = &obj->cylinder;
	t_cvec4		oc = ray_position - obj->coords; // Use obj->coords as the base center
	t_cvec4		d = normalize(cylinder->direction); // Ensure the direction is normalized
	t_cvec4		rd = orientation - d * dot_product(orientation, d);
	t_cvec4		oc_d = oc - d * dot_product(oc, d);

	t_cfloat	a = dot_product(rd, rd);
	t_cfloat	b = 2.0F * dot_product(rd, oc_d);
	t_cfloat	c = dot_product(oc_d, oc_d) - cylinder->radius * cylinder->radius;

	t_cfloat	discriminant = b * b - 4.0F * a * c;

	// Debugging information
	// printf("oc: (%f, %f, %f)\n", oc[0], oc[1], oc[2]);
	// printf("d: (%f, %f, %f)\n", d[0], d[1], d[2]);
	// printf("rd: (%f, %f, %f)\n", rd[0], rd[1], rd[2]);
	// printf("oc_d: (%f, %f, %f)\n", oc_d[0], oc_d[1], oc_d[2]);
	// printf("a: %f, b: %f, c: %f\n", a, b, c);
	// printf("discriminant: %f\n", discriminant);

	if (discriminant < 0) {
		return (-1.0F);
	}

	t_cfloat	fast_sqrt_discriminant = fast_sqrt(discriminant);
	t_cfloat	t1 = (-b - fast_sqrt_discriminant) / (2.0F * a);
	t_cfloat	t2 = (-b + fast_sqrt_discriminant) / (2.0F * a);

	// More debugging information
	// printf("t1: %f, t2: %f\n", t1, t2);

	if (t1 >= 0.0F && check_height(obj, cylinder, ray_position, orientation, t1)) {
		return (t1);
	} else if (t2 >= 0.0F && check_height(obj, cylinder, ray_position, orientation, t2)) {
		return (t2);
	}
	return (-1.0F);
}

void intersect_table(t_objs *obj, t_cvec4 coords, t_cvec4 orientation)
{
	static float	(*intersect_obj[NUM_OBJ_TYPES])(t_objs *, t_cvec4, t_cvec4) = {
		intersect_plane,
		intersect_sphere,
		intersect_cylinder
	};

	obj->hit = intersect_obj[obj->type](obj, coords, orientation);
}

uint32_t	vec_to_uint32(t_vec4 color)
{
	return (((uint32_t)(color[0] * 255) & 0xFF) << 24) |
			(((uint32_t)(color[1] * 255) & 0xFF) << 16) |
			(((uint32_t)(color[2] * 255) & 0xFF) << 8) |
			((uint32_t)(color[3] * 255) & 0xFF);
}

t_rgba	obj_nearest_vp(t_rt *rt, t_objs *objarr, t_cvec4 ray_position, t_cvec4 orientation)
{
	uint32_t	i;
	t_objs		*obj_closest_vp;
	t_rgba		color;

	obj_closest_vp = NULL;
	for (i = 0; i < rt->scene->arr_size; ++i)
	{
		intersect_table(&objarr[i], ray_position, orientation);
		if (objarr[i].hit > 0 && (obj_closest_vp == NULL || objarr[i].hit < obj_closest_vp->hit))
		{
			obj_closest_vp = &objarr[i];
			color = obj_closest_vp->color;
		}
	}
	if (obj_closest_vp != NULL)
	{

		return (color);
	}
	return ((t_rgba){0, 0, 0, 255});
}

void	set_pixel(t_window *win, uint16_t x, uint16_t y, t_rgba color)
{
	uint8_t	*pixels;

	pixels = win->img->pixels + (y * WINDOW_WIDTH + x) * 4;
	*(pixels++) = color.r;
	*(pixels++) = color.g;
	*(pixels++) = color.b;
	*(pixels++) = color.a;
}

void render_scene(t_rt *rt, t_scene *scn)
{
	t_cvec4		ray_position = scn->camera.coords;
	t_cuint32	bg_color = 0xFF0000;
	t_cfloat	scale = tan(scn->camera.camera.fov * 0.5F * (M_PI / 180.0F));
	t_cfloat	aspect_ratio_scale = ASPECT_RATIO * scale;
	float		x;
	float		y;
	
	for (uint32_t j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (uint32_t i = 0; i < WINDOW_WIDTH; i++)
		{
			x = (2.0F * (i + 0.5F) / (float)WINDOW_WIDTH - 1) * aspect_ratio_scale;
			y = (1.0F - 2.0F * (j + 0.5F) / (float)WINDOW_HEIGHT) * scale;
			t_vec4 orientation = normalize((t_vec4){x, y, -1.0F} + scn->camera.camera.orientation);
			t_rgba color = obj_nearest_vp(rt, scn->objarr, ray_position, orientation);

			// if (color != (t_rgba){0, 0, 0, 0})
			// {
				// puts("if");
				// mlx_put_pixel(rt->img, i, j, color);
				// printf("r%d\tg%d\tb%d\ta%d\n", color.r, color.g, color.b, color.a);
				// exit(0);
				set_pixel(rt->win, i, j, color);
			// }
			// else {
			// 	// puts("else");
			// }
		}
	}
}
