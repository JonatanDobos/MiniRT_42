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

void	T_print_fps(t_rt *rt, float fps)
{
	static float	fps_average;
	static uint8_t	counter;

	if (rt->win->res_ratio != rt->win->res_r_start)
		return ;
	fps_average += fps;
	++counter;
	if (counter != 20)
		return ;
	pthread_mutex_lock(rt->mtx + MTX_PRINT);
	printf("\r%4.1f fps", fps_average / (float)counter);
	fflush(stdout);
	pthread_mutex_unlock(rt->mtx + MTX_PRINT);
	counter = 0;
	fps_average = 0;
}

static void	render_routine(t_thread *th)
{
	double	time;

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
		T_print_fps(th->rt, 1.0F / time);
		printf("ratio: %hu\n", th->rt->win->res_ratio);
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
