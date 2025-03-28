#include <MLX42/MLX42.h>
#include <scene.h>
#include <utils.h>
#include <RTmlx.h>
#include <render.h>

void	set_starting_res_scale(t_rt *rt)
{
	double	time;

	rt->win->res_r_start = 10;
	rt->win->res_ratio = 10;
	if (THREADS > 1)
	{
		rt->win->img = rt->threads[0].img;
		rt->win->pixels = rt->threads[0].pixels_mlx;
	}
	rt->scene->render = true;
	time = mlx_get_time();
	render_manager(rt);
	time = mlx_get_time() - time;
	rt->win->res_r_start += (uint16_t)((time - 0.01F) * 50);
	printf("rndrscn: %d, resrat: %hu\n", rt->scene->render, rt->win->res_ratio);
	printf("time: %f,\tstart res_ratio: %hu\n", time, rt->win->res_r_start);
}
