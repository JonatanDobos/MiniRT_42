#include <miniRT.h>
#include <parsing.h>
#include <scene.h>
#include <RTmlx.h>
#include <utils.h>
#include <render.h>

void	init_main(t_rt *rt, t_scene *scn, t_scene *read_scn, t_window *win)
{
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

int main(int argc, char **argv)
{
	t_rt		rt;
	t_scene		sc;
	t_scene		read_sc;
	t_window	win;

	init_main(&rt, &sc, &read_sc, &win);
	if (SCREEN_WIDTH < 5 || SCREEN_HEIGHT < 5)
		return (write(1, "Screensize is too small\n", 35), EXIT_SUCCESS);
	if (input_parse(&rt, argv[1], &sc) != 0)
		return (cleanup(&rt), errset(ERTRN));
	if (windows_setup_mlx(&rt) != 0)
		return (cleanup(&rt), perr("MLX", errset(ERTRN)));
	init_hooks(&rt);
	if (THREADS > 1)
	{
		rt.scene->render_ongoing = true;
		if (multithreaded(&rt))
			return (errset(ERTRN));
	}
	mlx_loop(rt.win->mlx);
	cleanup(&rt);
	printf("exiting miniRT\n");
	return (EXIT_SUCCESS);
}
