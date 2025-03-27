#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>
#include <threadsRT.h>

//	Static functions
static void	render_routine(t_thread *th, uint16_t y);
static void	resynchronize_after_rendering(t_thread *th);

void	thread_routine_init(t_thread *th)
{
	pthread_mutex_lock(th->rt->mtx + MTX_SYNC);
	pthread_mutex_unlock(th->rt->mtx + MTX_SYNC);
	if (check_bool(th->rt->mtx + MTX_CREATION_CHECK, th->rt->thread_creation_check) == false)
	{
		return ;
	}
	render_routine(th, th->start_y);
}

// Ook iets doen wanneer de render onderbroken wordt?
static void	render_routine(t_thread *th, uint16_t start_y)
{
	double	time;

	while (check_bool(th->rt->mtx + MTX_QUIT_ROUTINE, th->rt->quit_routine) == false)
	{
		time = mlx_get_time();
		// printf("render thread %d\n", th->id);
		if (th->rt->win->res_ratio == RES_R_LOW)
			thread_first_render(th, start_y, 0);
		else if (thread_render(th, start_y, 0) == false)
			th->win->delta_time = mlx_get_time() - time;
		pthread_mutex_lock(th->rt->mtx + MTX_PRINT);
		printf("> res_ratio: %2hu > DTime: %.4f sec.\n", (uint16_t)th->win->res_ratio, th->win->delta_time);
		pthread_mutex_unlock(th->rt->mtx + MTX_PRINT);
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
