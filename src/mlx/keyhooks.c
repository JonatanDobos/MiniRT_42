#include <miniRT.h>
#include <RTmlx.h>
#include <scene.h>
#include <debug.h>

void	my_keyhook(mlx_key_data_t keydata, t_rt *rt)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS) {
		mlx_close_window(rt->win->mlx);
	}
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		print_camera(rt->scene->camera);
	}
	if (keydata.key == MLX_KEY_EQUAL && keydata.action == MLX_PRESS)
		return (res_upscale(rt));
	if (keydata.key == MLX_KEY_MINUS && keydata.action == MLX_PRESS)
		return (res_downscale(rt));
}

void	init_hooks(t_rt *rt)
{

	mlx_key_hook(rt->win->mlx, (mlx_keyfunc)my_keyhook, rt);
	mlx_loop_hook(rt->win->mlx, loop_hook, rt);
	mlx_scroll_hook(rt->win->mlx, fov_hook, rt->scene);
}
