#include "../extern_libraries/MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>

// #include <mlx.h>
#include <stdlib.h>

#define WIDTH 400
#define ASPECT_RATIO (16.0 / 9.0)
#define HEIGHT ((int)(WIDTH / ASPECT_RATIO))

void render_image(mlx_image_t* img) {
	// Image
	int image_width = WIDTH;
	int image_height = HEIGHT;

	// Render
	for (int j = 0; j < image_height; j++) {
		for (int i = 0; i < image_width; i++) {
			double r = (double)i / (image_width - 1);
			double g = (double)j / (image_height - 1);
			double b = 0.0;

			int ir = (int)(255.999 * r);
			int ig = (int)(255.999 * g);
			int ib = (int)(255.999 * b);

			int color = (ir << 24) | (ig << 16) | (ib << 8) | 0xFF;
			mlx_put_pixel(img, i, j, color);
		}
	}
}

int main(void) {
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Window", true);
	if (!mlx) {
		return EXIT_FAILURE;
	}

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img) {
		mlx_terminate(mlx);
		return EXIT_FAILURE;
	}

	render_image(img); // Call the new function to render the image

	mlx_image_to_window(mlx, img, 0, 0);

	mlx_loop(mlx); // Start the MLX loop

	mlx_terminate(mlx);
	return EXIT_SUCCESS;
}