/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:17 by jdobos        #+#    #+#                 */
/*   Updated: 2024/06/10 19:43:51 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

static void	create_mlx_basic(t_fractal *f, char *name)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	f->mlx = mlx_init(WIDTH_A, HEIGHT_A, name, true);
	if (!f->mlx)
		ft_error(f, "MLX init error");
	f->img = mlx_new_image(f->mlx, WIDTH_A, HEIGHT_A);
	if (!f->img || (mlx_image_to_window(f->mlx, f->img, 0, 0) < 0))
		ft_error(f, "MLX image error");
}

// Creates an mlx window with two images:
// one on the left half (mandelbrot) (1:1)ratio
// one on the right half (julia) (1:1)ratio
static void	create_mlx_split(t_fractal *f)
{
	mlx_set_setting(MLX_MAXIMIZED, false);
	f->mlx = mlx_init(S_WIDTH, S_HEIGHT, "~ Split Screen ~", false);
	if (!f->mlx)
		ft_error(f, "MLX init error");
	f->img = mlx_new_image(f->mlx, M_WIDTH, M_HEIGHT);
	if (!f->img || (mlx_image_to_window(f->mlx, f->img, 0, 0) < 0))
		ft_error(f, "MLX image mandelbrot error");
	f->img_j = mlx_new_image(f->mlx, J_WIDTH, J_HEIGHT);
	if (!f->img_j || (mlx_image_to_window(f->mlx, f->img_j, M_WIDTH, 0) < 0))
		ft_error(f, "MLX image julia error");
}

void	fractol(char *name, t_fractal *f)
{
	init_color(f);
	if (f->split == true)
	{
		create_mlx_split(f);
		assign_hooks_split(f);
		init_split_struct(f);
		re_init_palette(f, julia);
	}
	else
	{
		create_mlx_basic(f, name);
		assign_hooks_basic(f);
		init_basic_struct(f);
	}
	re_init_palette(f, mandel);
	mlx_loop(f->mlx);
	close_all(f);
}

int32_t	main(int argc, char **argv)
{
	t_fractal	f;

	init_null(&f);
	if (argc != 2 && argc != 3)
		ft_error(&f, ERR_MESSAGE);
	f.split = false;
	f.set = mandel;
	if (!(ft_strncmp(argv[1], "mandelbrot", 11)))
		f.set = mandel;
	else if (!(ft_strncmp(argv[1], "julia", 6)))
		f.set = julia;
	else if (!(ft_strncmp(argv[1], "split", 6)))
		f.split = true;
	else
		ft_error(&f, ERR_MESSAGE);
	f.julia_x = -1.2;
	f.julia_y = 0.0;
	if (argc == 3 && arg_check(&f, argv[2]))
		assign_jul_c(&f, argv[2]);
	fractol(argv[1], &f);
	return (EXIT_SUCCESS);
}
