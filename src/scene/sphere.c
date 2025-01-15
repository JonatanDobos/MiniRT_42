#include <miniRT.h>

//      Draws a sphere

// void draw_sphere(t_rt *rt, t_sphere *sphere)
// {
// 	int x, y;
// 	float distance;
// 	t_vec color = sphere->color;

// 	for (y = 0; y < HEIGHT; y++)
// 	{
// 		for (x = 0; x < WIDTH; x++)
// 		{
// 			float dist = sqrt(pow(x - WIDTH / 2, 2) + pow(y - HEIGHT / 2, 2));
// 			if (dist < sphere->radius)
// 			{
// 				int red = (int)color.r;
// 				int green = (int)color.g;
// 				int blue = (int)color.b;
// 				mlx_put_pixel(rt->img, x, y, 0x00FFFF);
// 			}
// 			else
// 			{
// 				mlx_put_pixel(rt->img, x, y, 0xFF0000);
// 			}
// 		}
// 	}
// }

// int main(void)
// {
// 	t_rt rt;
// 	t_sphere sphere;

// 	rt.mlx = mlx_init(WIDTH, HEIGHT, "Sphere Showcase", true);
// 	if (!rt.mlx)
// 	{
// 		printf("Failed to initialize MLX\n");
// 		return (EXIT_FAILURE);
// 	}
// 	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
// 	if (!rt.img)
// 	{
// 		printf("Failed to create image\n");
// 		mlx_terminate(rt.mlx);
// 		return (EXIT_FAILURE);
// 	}

// 	sphere.center = (t_vec){.i = 0, .j = 0, .k = 0};
// 	sphere.radius = 100;
// 	sphere.color = (t_vec){.i = 255, .j = 0, .k = 0}; // Red color

// 	draw_sphere(&rt, &sphere);

// 	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
// 	mlx_loop(rt.mlx);

// 	mlx_terminate(rt.mlx);
// 	return (EXIT_SUCCESS);
// }



t_sphere create_sphere(t_vec center, double radius, t_vec color)
{
	t_sphere sphere;
	sphere.center = center;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

double dot(const t_vec *v1, const t_vec *v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

int intersect_sphere(const t_sphere *sphere, const t_vec *ray_direction, const t_vec *ray_pos)
{
	t_vec oc = {
		.x = ray_pos->x - sphere->center.x,
		.y = ray_pos->y - sphere->center.y,
		.z = ray_pos->z - sphere->center.z
	};

	double a = dot(ray_direction, ray_direction);
	double b = 2.0 * dot(&oc, ray_direction);
	double c = dot(&oc, &oc) - sphere->radius * sphere->radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		// puts("No intersection: discriminant < 0");
		return 0;
	}
	else
	{
		double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
		double t1 = (-b + sqrt(discriminant)) / (2.0 * a);

		// printf("First t: %f\n", t0);
		// printf("Second t: %f\n", t1);

		if (t0 > t1)
		{
			double temp = t0;
			t0 = t1;
			t1 = temp;
		}

		if (t0 < 0)
		{
			t0 = t1;
			if (t0 < 0)
			{
				// puts("No intersection: both t0 and t1 < 0");
				return 0;
			}
		}
		return 1;
	}
}

t_vec snormalize(t_vec v)
{
	double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length > 0)
	{
		v.x /= length;
		v.y /= length;
		v.z /= length;
	}
	return v;
}

void render_sphere(mlx_image_t *img, const t_sphere *sphere, const t_vp *vp)
{
	const t_vec *ray_pos = &vp->ray_position;
	const t_vec *base_ray_dir = &vp->ray_direction;
	uint32_t bg_color = 0xFF0000; // Background color
	uint32_t color = 0xFFFFFF;    // Sphere color

	double aspect_ratio = (double)WIDTH / HEIGHT;
	// double aspect_ratio = (double)HEIGHT / WIDTH;

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			t_vec ray_direction = {
				.x = base_ray_dir->x + (2.0 * ((i + 0.5) / WIDTH) - 1.0) * aspect_ratio,
				.y = base_ray_dir->y + (1.0 - 2.0 * ((j + 0.5) / HEIGHT)),
				.z = base_ray_dir->z
			};
			ray_direction = snormalize(ray_direction);

			if (intersect_sphere(sphere, &ray_direction, ray_pos))
			{
				mlx_put_pixel(img, i, j, color);
			}
			else
			{
				// mlx_put_pixel(img, i, j, bg_color);
			}
		}
	}
}

t_sphere sphere(t_rt *rt)
{
	t_sphere sphere = {
		.center = {.x = 0.0, .y = 0.0, .z = 0.0},
		.radius = 3.0,
		.color = {.r = 1.0, .g = 0.0, .b = 1.0}
	};

	render_sphere(rt->img, &sphere, &rt->vp);
	return sphere;
}