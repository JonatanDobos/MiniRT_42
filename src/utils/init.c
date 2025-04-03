#include <MLX42/MLX42.h>
#include <scene.h>
#include <utils.h>
#include <RTmlx.h>
#include <render.h>
#include <RTerror.h>

void	init_main(t_rt *rt, t_scene *scn, t_scene *read_scn, t_window *win)
{
	const float	scrsize_multiplier = ((float)(SCREEN_HEIGHT + SCREEN_WIDTH) * 0.000001F);

	ft_bzero(rt, sizeof(t_rt));
	ft_bzero(scn, sizeof(t_scene));
	ft_bzero(read_scn, sizeof(t_scene));
	ft_bzero(win, sizeof(t_window));
	errset((int64_t)&rt->errnum);
	rt->scene = scn;
	rt->read_scene = read_scn;
	rt->win = win;
	rt->win->res_ratio = 1;
	scn->render = true;
	rt->win->res_r_start = RES_RATIO_MAX;
	win->delta_time = 0.1F;
	win->target_time = 0.002F + scrsize_multiplier;
}

int32_t	multithreaded(t_rt *rt)
{
	if (init_read_scene(rt->scene, rt->read_scene))
		return (perr("read_scene", errset(ERTRN)), cleanup(rt));
	rt->mtx_init_check = true;
	if (initialize_mutexes(rt) == false)
		return (false);
	if (pthread_cond_init(&rt->cond, NULL) != 0)
	{
		fprintf(stderr, "Failed to initialize condition variable\n");
		exit(EXIT_FAILURE);
	}
	rt->creation_check = true;
	if (launch_pthreads(rt) == false)
	{
		return (perr("Pthread", errset(ERTRN)), cleanup(rt));
	}
	pthread_mutex_lock(rt->mtx + MTX_RESYNC);
	pthread_mutex_unlock(rt->mtx + MTX_SYNC);
	return (EXIT_SUCCESS);
}

void	set_starting_res_ratio(t_rt *rt, double delta_time)
{
	const double	error = delta_time - rt->win->target_time;
	const double	adjustment_factor = 10.0F;
	const double	new_ratio = rt->win->res_r_start * (1.0F + (error * adjustment_factor));

	rt->win->res_r_start = intclamp((int)new_ratio, 2, 30);
}
