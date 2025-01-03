#include "../includes/miniRT.h"

// void render_image(mlx_image_t* img)
// {
// 	int image_width = WIDTH;
// 	int image_height = HEIGHT;

// 	t_rgb color;
// 	for (int j = 0; j < image_height; j++) {
// 		printf("\rScanlines remaining: %d ", HEIGHT - j);
// 		for (int i = 0; i < image_width; i++) {
// 			double r = (double)i / (image_width - 1);
// 			double g = (double)j / (image_height - 1);
// 			double b = 0.0;

// 			color.r = (int)(255.999 * r);
// 			color.g = (int)(255.999 * g);
// 			color.b = (int)(255.999 * b);
// 			color.a = 255;
// 			mlx_put_pixel(img, i, j, color.rgba);
// 		}
// 	}
// 	printf("\r\rAll pixels are printed                   \n");
// }

static void	initiliaze_structs(t_rt *rt)
{
	ft_bzero(rt, sizeof(t_rt));
}

static void	clear_everything(t_rt *rt)
{
	mlx_delete_image(rt->mlx, rt->img);
	mlx_terminate(rt->mlx);
}

int main(void) {
	t_rt	rt;

	initiliaze_structs(&rt);
	rt.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!rt.mlx) {
		return (EXIT_FAILURE);
	}
	puts("hier dan");

	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	if (rt.img == NULL) {
		mlx_terminate(rt.mlx);
		return (EXIT_FAILURE);
	}

	rt.ray_origin = (t_vec) {.x = 0.0, .y = 0.0, .z = 5.0};

	// render_image(rt.img); // Call the new function to render the image
	t_plane pln = plane(&rt);
	rt.plane = &pln;

	t_sphere sphr = sphere(&rt);
	rt.sphere = &sphr;

	mlx_image_to_window(rt.mlx, rt.img, 0, 0);
	mlx_key_hook(rt.mlx, (t_mlx_keyhook_cast)my_keyhook, &rt);
puts("here???");
	mlx_loop(rt.mlx); // Start the MLX loop

	clear_everything(&rt);
	return (EXIT_SUCCESS);
}

