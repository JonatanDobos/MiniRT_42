#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>
#include <threadsRT.h>
#include <setup_clean.h>

//	Static functions
static void	render_routine(t_thread *th);
static void	resynchronize_after_rendering(t_thread *th);

void	*thread_routine_init(t_thread *th)
{
	pthread_mutex_lock(th->rt->mtx + MTX_SYNC);
	pthread_mutex_unlock(th->rt->mtx + MTX_SYNC);
	render_routine(th);
	return (NULL);
}

void	print_performance_stats(t_rt *rt, float fps)
{
	static float	fps_average = 0.0F;
	static uint8_t	counter = 0;
	static double	last_print_time = 0.0;
	// char			string[32];

	if (rt->win->res_ratio != rt->win->res_r_start)
		return ;
	puts("YOOOO");
	fps_average += fps;
	++counter;
	if (mlx_get_time() < last_print_time + 40.0)
		return ;
	last_print_time = mlx_get_time();
	if (PRINT_PERFORMANCE == true)
	{
		pthread_mutex_lock(rt->mtx + MTX_PRINT);
		// ft_putchar_fd('\r', STDOUT_FILENO);
		// ft_putstr_fd("", STDOUT_FILENO);
		printf("\r%4.1f fps", fps_average / (float)counter);
		fflush(stdout);
		pthread_mutex_unlock(rt->mtx + MTX_PRINT);
	}
	counter = 0;
	fps_average = 0;
}

static void	render_routine(t_thread *th)
{
	static double	begin_time = 0.0;
	double	time;

	if (begin_time == 0.0)
		begin_time = mlx_get_time();
	while (check_bool(th->rt->mtx + MTX_QUIT_ROUTINE, th->rt->quit_routine) == false)
	{
		time = mlx_get_time();
		if (th->rt->win->res_ratio == th->win->res_r_start)
		{
			thread_fast_render(th, th->rt->win);
			time = mlx_get_time() - time;
			th->win->delta_time = time;
		}
		else if (thread_render(th, th->rt->win) == false)
		{
			time = mlx_get_time() - time;
			if (th->win->res_ratio == th->win->res_r_start - 1)
				set_starting_res_ratio(th->rt, time);
		}
		// print_performance_stats(th->rt, 1.0F / time);
		printf("ratio: %hu\n", th->rt->win->res_ratio);
		if (th->rt->win->res_ratio == 1)
			printf("%.2f ms\n", (time - begin_time) * 1000.0);
		resynchronize_after_rendering(th);
	}
	pthread_mutex_lock(th->rt->mtx + MTX_STOPPED_THREADS);
	++th->rt->stopped_threads;
	pthread_cond_signal(&th->rt->cond);
	pthread_mutex_unlock(th->rt->mtx + MTX_STOPPED_THREADS);
}

static void	resynchronize_after_rendering(t_thread *th)
{
	pthread_mutex_lock(th->rt->mtx + MTX_DONE_RENDERING);
	++th->rt->finished_rendering;
	pthread_mutex_unlock(th->rt->mtx + MTX_DONE_RENDERING);

	pthread_mutex_lock(th->rt->mtx + MTX_RESYNC);
	--th->rt->finished_rendering;
	pthread_cond_signal(&th->rt->cond);
	pthread_mutex_unlock(th->rt->mtx + MTX_RESYNC);

	pthread_mutex_lock(th->rt->mtx + MTX_SYNC);
	pthread_mutex_unlock(th->rt->mtx + MTX_SYNC);
}
