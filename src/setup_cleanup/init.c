#include <MLX42/MLX42.h>
#include <scene.h>
#include <setup_clean.h>
#include <RTmlx.h>
#include <render.h>
#include <RTerror.h>
#include <mathRT.h>
#include <parsing.h>

#define NO_FILENAME "Give argument: ./miniRT <filename>\n"
#define SCREEN_ERROR "Screensize is too small\n"

void	init_main(t_rt *rt, t_scene *scn, t_scene *read_scn, t_window *win)
{
	float	screen_size_multiplier;

	screen_size_multiplier = ((float)(SCREEN_HEIGHT + SCREEN_WIDTH) * 0.000001F);
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
	win->target_time = 0.002F + screen_size_multiplier;
}

int16_t	setup_init_parsing(t_rt *rt, const int argc, const char *argv)
{
	if (argc != 2)
		return (write(1, NO_FILENAME, sizeof(NO_FILENAME) - 1), EXIT_FAILURE);
	else if (SCREEN_WIDTH < 5 || SCREEN_HEIGHT < 5)
		return (write(1, SCREEN_ERROR, sizeof(SCREEN_ERROR) - 1), EXIT_FAILURE);
	else if (parse_scene_file(argv, rt->scene) != 0)
		return (cleanup(rt), errset(ERTRN));
	else if (windows_setup_mlx(rt) != 0)
		return (cleanup(rt), perr("MLX", errset(ERTRN)));
	rt->win->target_time += (float)(rt->scene->l_arr_size + rt->scene->o_arr_size) * 0.0005F;
	rt->win->target_time = clamp(rt->win->target_time, 0.01F, 0.025F);
	return (EXIT_SUCCESS);
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
