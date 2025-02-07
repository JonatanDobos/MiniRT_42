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
}








void	my_screw_you_joni_render(t_rt *rt)
{
	pthread_mutex_lock(rt->mtx + MTX_SYNC);
	pthread_mutex_unlock(rt->mtx + MTX_SYNC);
	pthread_mutex_lock(rt->mtx + MTX_CREATION_CHECK);
	if (rt->thread_creation_check == false)
	{
		pthread_mutex_unlock(rt->mtx + MTX_CREATION_CHECK);
		return ;
	}
	pthread_mutex_unlock(rt->mtx + MTX_CREATION_CHECK);
	printf("threads are created\n");
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
	if (init_pthread_mutex(&rt) == false ||
		launch_pthreads(&rt) == false)
	{
		return (perr("Pthread", errset(ERTRN)), cleanup(&rt));
	}
	rt.scene->render = true;
	printf("miniRT finished rendering %f\n", mlx_get_time());
	mlx_loop(rt.win->mlx);
	cleanup(&rt);
	printf("exiting miniRT\n");
	return (EXIT_SUCCESS);
}
