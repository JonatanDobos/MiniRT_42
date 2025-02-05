#include <miniRT.h>
#include <RTmlx.h>
#include <scene.h>
#include <debug.h>

#include <stdio.h>

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt)
{
	bool	pressed_key = (keydata.action == MLX_PRESS);

	if (pressed_key == true)
	{
		if (handle_object_modification(keydata.key, rt->scene) == true)
			return ;
		if (keydata.key == MLX_KEY_1)
			print_camera(rt->scene->camera);
		if (keydata.key == MLX_KEY_EQUAL)
			rt->scene->render = res_upscale(rt->win);
		else if (keydata.key == MLX_KEY_MINUS)
			rt->scene->render = res_downscale(rt->win);
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(rt->win->mlx);
	}
}

void	init_hooks(t_rt *rt)
{

	mlx_key_hook(rt->win->mlx, (mlx_keyfunc)my_keyhook, rt);
	mlx_loop_hook(rt->win->mlx, (mlx_closefunc)loop_hook, rt);
	// mlx_mouse_hook(rt->win->mlx, loop_hook, rt);
	mlx_scroll_hook(rt->win->mlx, (mlx_cursorfunc)fov_hook, rt->scene);
}
