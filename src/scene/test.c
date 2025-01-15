#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>

float	intersect_plane(t_objs *obj, const t_vec3 coords, const t_vec3 ray_direction)
{
	t_plane *plane = &obj->plane;
	float intersection_distance;
	float denom = dot_product(plane->direction, coords);
	if (fabs(denom) > 1e-6) {
		t_vec3 p0l0 = obj->ray_direction - ray_direction;
		intersection_distance = dot_product(p0l0, plane->direction) / denom;
		if (intersection_distance >= 0) {
			return (intersection_distance);
		}
	}
	return (-1);
}

float	intersect_sphere(t_objs *obj, const t_vec3 coords, const t_vec3 ray_direction)
{
	float radius = obj->sphere.radius;
	t_vec3 oc = ray_direction - obj->ray_direction;

	float a = dot_product(coords, coords);
	float b = 2.0 * dot_product(oc, coords);
	float c = dot_product(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant > 0)
	{
		float t0 = (-b - sqrt(discriminant)) / (2.0 * a);
		float t1 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t0 > 0 && t1 > 0)
		{
			return ((t0 < t1) ? t0 : t1); // Choose the closest positive t value
		}
		else
		{
			return ((t0 > 0) ? t0 : t1); // Choose the positive t value if only one is positive
		}
	}
	return (-1);
}

void intersect_table(t_objs *obj, const t_vec3 coords, const t_vec3 ray_direction)
{
	static float (*intersect_obj[NUM_OBJ_TYPES])(t_objs *, const t_vec3, const t_vec3) = {
		intersect_plane,
		intersect_sphere
	};

	obj->hit = intersect_obj[obj->type](obj, coords, ray_direction);
}

uint32_t	vec_to_uint32(t_vec3 color)
{
	return (((uint32_t)(color[0] * 255) & 0xFF) << 24) |
			(((uint32_t)(color[1] * 255) & 0xFF) << 16) |
			(((uint32_t)(color[2] * 255) & 0xFF) << 8) |
			((uint32_t)(color[3] * 255) & 0xFF);
}

uint32_t	obj_nearest_vp(t_rt *rt, t_objs *objarr, const t_vec3 coords, const t_vec3 ray_direction)
{
	size_t	i;
	t_objs	*obj_closest_vp = NULL;
	t_vec3	color;
	for (i = 0; i < rt->scene->arr_size; ++i)
	{
		intersect_table(&objarr[i], coords, ray_direction);
		if (objarr[i].hit > 0 && (obj_closest_vp == NULL || objarr[i].hit < obj_closest_vp->hit))
		{
			obj_closest_vp = &objarr[i];
			color = obj_closest_vp->color;
		}
	}
	if (obj_closest_vp != NULL)
	{
		return (vec_to_uint32(color));
	}
	return (0);
}

void render_scene(t_rt *rt, t_scene *scn)
{
	const t_vec3 base_ray_dir = scn->camera.camera.coords;
	uint32_t bg_color = 0xFF0000;

	float aspect_ratio = (float)WINDOW_WIDTH / WINDOW_HEIGHT;

	for (int j = 0; j < WINDOW_HEIGHT; j++)
	{
		for (int i = 0; i < WINDOW_WIDTH; i++)
		{
			t_vec3 offset = {
				(2.0 * ((i + 0.5) / WINDOW_WIDTH) - 1.0) * aspect_ratio,
				(1.0 - 2.0 * ((j + 0.5) / WINDOW_HEIGHT)),
				0.0
			};
			t_vec3 coords = normalize(base_ray_dir + offset);
			uint32_t color = obj_nearest_vp(rt, scn->objarr, coords, scn->camera.ray_direction);
			if (color != 0)
			{
				mlx_put_pixel(rt->img, i, j, color);
			}
		}
	}
}


// void generate_rays(t_camera *camera, int image_WINDOW_WIDTH, int image_WINDOW_HEIGHT, t_vec3 *rays)
// {
// 	float aspect_ratio = (float)image_WINDOW_WIDTH / (float)image_WINDOW_HEIGHT;
// 	float fov_radians = camera->fov * (M_PI / 180.0); // Convert FOV to radians
// 	float half_WINDOW_HEIGHT = tan(fov_radians / 2);
// 	float half_WINDOW_WIDTH = aspect_ratio * half_WINDOW_HEIGHT;

// 	t_vec3 forward = normalize(camera->coords);
// 	t_vec3 right = normalize(cross_product((t_vec3){0, 1, 0}, forward)); // Assuming up vector is (0, 1, 0)
// 	t_vec3 up = cross_product(forward, right);

// 	for (int y = 0; y < image_WINDOW_HEIGHT; ++y) {
// 		for (int x = 0; x < image_WINDOW_WIDTH; ++x) {
// 			float u = (2.0 * ((x + 0.5) / image_WINDOW_WIDTH) - 1.0) * half_WINDOW_WIDTH;
// 			float v = (1.0 - 2.0 * ((y + 0.5) / image_WINDOW_HEIGHT)) * half_WINDOW_HEIGHT;

// 			t_vec3 coords = normalize((t_vec3){
// 				u * right[0] + v * up[0] - forward[0],
// 				u * right[1] + v * up[1] - forward[1],
// 				u * right[2] + v * up[2] - forward[2]
// 			});

// 			rays[y * image_WINDOW_WIDTH + x] = coords;
// 		}
// 	}
// }

// void render_scene(t_rt *rt, t_scene *scn)
// {
// 	t_vec3 *rays = malloc(SCREEN_WINDOW_WIDTH * SCREEN_WINDOW_HEIGHT * sizeof(t_vec3));
// 	generate_rays(&scn->camera.camera, SCREEN_WINDOW_WIDTH, SCREEN_WINDOW_HEIGHT, rays);

// 	uint32_t bg_color = 0xFF0000;

// 	for (int j = 0; j < SCREEN_WINDOW_HEIGHT; j++)
// 	{
// 		for (int i = 0; i < SCREEN_WINDOW_WIDTH; i++)
// 		{
// 			t_vec3 coords = rays[j * SCREEN_WINDOW_WIDTH + i];
// 			t_vec3 ray_pos = scn->camera.ray_direction;
// 			uint32_t color = obj_nearest_vp(rt, scn->objarr, coords, ray_pos); // return obj or NULL if nothing hits.
// 			if (color != 0)
// 			{
// 				// puts("OKE");
// 				// sleep(3);
// 				mlx_put_pixel(rt->img, i, j, color);
// 			}
// 			else
// 			{
// 				// puts("or here?");
// 				mlx_put_pixel(rt->img, i, j, bg_color);
// 			}
// 		}
// 	}

// 	free(rays);
// }