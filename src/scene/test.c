#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>

float intersect_plane(t_objs *obj, const t_vec3 ray_dir, const t_vec3 ray_pos)
{
    t_plane *plane = &obj->plane;
    float intersection_distance;
    float denom = dot_product(plane->direction, ray_dir); // Using dot product
    if (fabs(denom) > 1e-6) {
        t_vec3 p0l0 = obj->coords - ray_pos; // Using vector subtraction
        intersection_distance = dot_product(p0l0, plane->direction) / denom; // Using dot product
        if (intersection_distance >= 0) {
            return (intersection_distance);
        }
    }
    return (-1);
}

float intersect_sphere(t_objs *obj, const t_vec3 ray_dir, const t_vec3 ray_pos)
{
	float radius = obj->sphere.radius;
	t_vec3 oc = ray_pos - obj->coords; // Using vector subtraction

	float a = dot_product(ray_dir, ray_dir); // Using dot product
	float b = 2.0 * dot_product(oc, ray_dir); // Using dot product
	float c = dot_product(oc, oc) - radius * radius; // Using dot product
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

void intersect_table(t_objs *obj, const t_vec3 ray_dir, const t_vec3 ray_pos)
{
	static float (*intersect_obj[NUM_OBJ_TYPES])(t_objs *, const t_vec3, const t_vec3) = {
		intersect_plane,
		intersect_sphere
	};

	obj->hit = intersect_obj[obj->type](obj, ray_dir, ray_pos);
}

uint32_t	vec_to_uint32(t_vec3 color)
{
	return (((uint32_t)(color[0] * 255) & 0xFF) << 24) |
			(((uint32_t)(color[1] * 255) & 0xFF) << 16) |
			(((uint32_t)(color[2] * 255) & 0xFF) << 8) |
			((uint32_t)(color[3] * 255) & 0xFF);
}

uint32_t	obj_nearest_vp(t_rt *rt, t_objs *objarr, const t_vec3 ray_dir, const t_vec3 ray_pos)
{
	size_t	i;
	t_objs	*obj_closest_vp = NULL;
	t_vec3	color;
	for (i = 0; i < rt->scene->arr_size; ++i)
	{
		intersect_table(&objarr[i], ray_dir, ray_pos);
		if (objarr[i].hit > 0 && (obj_closest_vp == NULL || objarr[i].hit < obj_closest_vp->hit))
		{
			obj_closest_vp = &objarr[i];
			color = obj_closest_vp->color;
		}
	}
	// intersect_table(&objarr[0], ray_dir, ray_pos);
	// if (objarr[0].hit > 0) {
	// 	obj_closest_vp = &objarr[0];
	// }
	// for (i = 1; i < rt->scene.arr_size; ++i) {
	// 	intersect_table(&objarr[i], ray_dir, ray_pos);
	// 	if (objarr[i].hit > 0 && objarr[i].hit < obj_closest_vp->hit) {
	// 		obj_closest_vp = &objarr[i];
	// 	}
	// }

	if (obj_closest_vp != NULL)
	{
		return (vec_to_uint32(color)); // Assuming color is a field in t_objs
	}
	return (0);
}

// void render_scene(t_rt *rt, mlx_image_t *img, t_objs *objarr, t_vp *vp)
void render_scene(t_rt *rt, t_scene *scn)
{
	const t_vec3 base_ray_dir = scn->camera.camera.ray_direction;
	uint32_t bg_color = 0xFF0000;

	float aspect_ratio = (float)WIDTH / HEIGHT;

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			t_vec3 offset = {
				(2.0 * ((i + 0.5) / WIDTH) - 1.0) * aspect_ratio,
				(1.0 - 2.0 * ((j + 0.5) / HEIGHT)),
				0.0
			};
			t_vec3 ray_direction = normalize(base_ray_dir + offset);
			uint32_t color = obj_nearest_vp(rt, scn->objarr, ray_direction, scn->camera.coords);	// return obj or NULL if nothing hits.
			if (color != 0)
			{
				mlx_put_pixel(rt->img, i, j, color);
			}
			// else
			// {
			// 	mlx_put_pixel(rt->img, i, j, bg_color);
			// }
		}
	}
}


// void generate_rays(t_camera *camera, int image_width, int image_height, t_vec3 *rays)
// {
// 	float aspect_ratio = (float)image_width / (float)image_height;
// 	float fov_radians = camera->fov * (M_PI / 180.0); // Convert FOV to radians
// 	float half_height = tan(fov_radians / 2);
// 	float half_width = aspect_ratio * half_height;

// 	t_vec3 forward = normalize(camera->ray_direction);
// 	t_vec3 right = normalize(cross_product((t_vec3){0, 1, 0}, forward)); // Assuming up vector is (0, 1, 0)
// 	t_vec3 up = cross_product(forward, right);

// 	for (int y = 0; y < image_height; ++y) {
// 		for (int x = 0; x < image_width; ++x) {
// 			float u = (2.0 * ((x + 0.5) / image_width) - 1.0) * half_width;
// 			float v = (1.0 - 2.0 * ((y + 0.5) / image_height)) * half_height;

// 			t_vec3 ray_direction = normalize((t_vec3){
// 				u * right[0] + v * up[0] - forward[0],
// 				u * right[1] + v * up[1] - forward[1],
// 				u * right[2] + v * up[2] - forward[2]
// 			});

// 			rays[y * image_width + x] = ray_direction;
// 		}
// 	}
// }

// void render_scene(t_rt *rt, t_scene *scn)
// {
// 	t_vec3 *rays = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(t_vec3));
// 	generate_rays(&scn->camera.camera, SCREEN_WIDTH, SCREEN_HEIGHT, rays);

// 	uint32_t bg_color = 0xFF0000;

// 	for (int j = 0; j < SCREEN_HEIGHT; j++)
// 	{
// 		for (int i = 0; i < SCREEN_WIDTH; i++)
// 		{
// 			t_vec3 ray_direction = rays[j * SCREEN_WIDTH + i];
// 			t_vec3 ray_pos = scn->camera.coords;
// 			uint32_t color = obj_nearest_vp(rt, scn->objarr, ray_direction, ray_pos); // return obj or NULL if nothing hits.
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