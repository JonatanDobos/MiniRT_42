#include <miniRT.h>
#include <RTmlx.h>

void	my_keyhook(mlx_key_data_t keydata, t_window *win)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(win->mlx);
	// if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	// {
	// 	rt->plane->direction.x += 0.1;
	// 	printf("x value = %f\n", rt->plane->direction.x);
	// 	render_plane(rt->img, rt->plane, &rt->ray_origin);
	// }
	// if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	// {
	// 	rt->plane->direction.x -= 0.1;
	// 	printf("x value = %f\n", rt->plane->direction.x);
	// 	render_plane(rt->img, rt->plane, &rt->ray_origin);
	// }

	// if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
	// {
	// 	rt->plane->direction.y += 0.1;
	// 	printf("y value = %f\n", rt->plane->direction.y);
	// 	render_plane(rt->img, rt->plane, &rt->ray_origin);
	// }
	// if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	// {
	// 	rt->plane->direction.y -= 0.1;
	// 	printf("y value = %f\n", rt->plane->direction.y);
	// 	render_plane(rt->img, rt->plane, &rt->ray_origin);
	// }

	// if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
	// {
	// 	rt->plane->direction.z += 0.1;
	// 	printf("z value = %f\n", rt->plane->direction.z);
	// 	render_plane(rt->img, rt->plane, &rt->ray_origin);
	// }
	// if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
	// {
	// 	rt->plane->direction.z -= 0.1;
	// 	printf("z value = %f\n", rt->plane->direction.z);
	// 	render_plane(rt->img, rt->plane, &rt->ray_origin);
	// }

}

void	init_hooks(t_rt *m)
{
	// mlx_close_hook(m->win.mlx, close_mlx, m);
	mlx_key_hook(m->win->mlx, (mlx_keyfunc)my_keyhook, m);
	mlx_loop_hook(m->win->mlx, loop_hook, m);
	mlx_scroll_hook(m->win->mlx, fov_hook, &m->scene);
}
