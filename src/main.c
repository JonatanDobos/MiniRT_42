#include <miniRT.h>
#include <parsing.h>
#include <scene.h>
#include <RTmlx.h>
#include <utils.h>

bool	check_input(t_rt *rt, int argc, char **argv)
{
	(void)rt;
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

void	init_main(t_rt *rt, t_scene *scn, t_window *win)
{
	ft_bzero(rt, sizeof(t_rt));
	ft_bzero(scn, sizeof(t_scene));
	ft_bzero(win, sizeof(t_window));
	errset((int64_t)rt->errnum);
	rt->scene = scn;
	rt->win = win;
	rt->win->res_ratio = 1.0F;
	rt->thread_creation_check = true;
	scn->render = true;
}

int32_t	multithreaded(t_rt *rt)
{
	if (create_and_launch_mutex(rt) == false)
		return (false);
	if (launch_pthreads(rt) == false)
	{
		return (perr("Pthread", errset(ERTRN)), cleanup(rt));
	}
	pthread_mutex_unlock(rt->mtx + MTX_SYNC);
}

int main(int argc, char **argv)
{
	t_rt		rt;
	t_scene		sc;
	t_window	win;

	init_main(&rt, &sc, &win);
	if (check_input(&rt, argc, argv) == EXIT_FAILURE || \
		input_parse(&rt, argv[1]) != 0 || \
		windows_setup_mlx(&rt) == EXIT_FAILURE)
	{
		return (perr("Parsing", errset(ERTRN)), cleanup(&rt));
	}
	init_hooks(&rt);
	if (THREADS > 1)
		multithreaded(&rt);
	mlx_loop(rt.win->mlx);
	cleanup(&rt);
	printf("exiting miniRT\n");
	return (EXIT_SUCCESS);
}
