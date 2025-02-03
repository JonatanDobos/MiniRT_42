#include <miniRT.h>
#include <RTmlx.h>
#include <scene.h>
#include <debug.h>

#include <stdio.h>

void	func(t_rt *rt)
{
	// if (rt->scene->objs[1].type == CYLINDER)
	// 	printf("hiero\n", 1);
	// float old = rt->scene->objs[1].cylinder.height;
	// float increase = rt->scene->objs[1].cylinder.height * 1.1F;
	// float add = increase - old;
	rt->scene->objs[1].cylinder.height *= 1.1F;
	// print_cylinder(rt->scene->objs[1]);
	rt->scene->render = true;
}

void	func2(t_rt *rt)
{
	// if (rt->scene->objs[1].type == CYLINDER)
	// 	printf("hiero\n", 1);
	rt->scene->objs[1].cylinder.radius *= 1.1F;
	print_cylinder(rt->scene->objs[1]);
	rt->scene->render = true;
}

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_COMMA && keydata.action == MLX_PRESS)
		func(rt);
	if (keydata.key == MLX_KEY_PERIOD && keydata.action == MLX_PRESS)
		func2(rt);
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		print_camera(rt->scene->camera);
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		return (res_upscale(rt));
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		return (res_downscale(rt));
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(rt->win->mlx);
}

void	init_hooks(t_rt *rt)
{

	mlx_key_hook(rt->win->mlx, (mlx_keyfunc)my_keyhook, rt);
	mlx_loop_hook(rt->win->mlx, loop_hook, rt);
	mlx_scroll_hook(rt->win->mlx, fov_hook, rt->scene);
}
