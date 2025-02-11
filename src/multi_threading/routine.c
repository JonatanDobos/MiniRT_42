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

static void	render_routine(t_thread *th, uint16_t y)
{
	while (check_bool(th->rt->mtx + MTX_QUIT_ROUTINE, th->rt->quit_routine) == false)
	{
		pthread_mutex_lock(th->rt->mtx + MTX_RENDER);
		if (th->rt->scene->render_ongoing == true)
		{
			render_upscale_thread(th);
		}
		pthread_mutex_unlock(th->rt->mtx + MTX_RENDER);
		if (thread_render(th, y, 0) == true)
			continue ;
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
	// print_lock(th->rt->mtx + MTX_RENDER, "check");

	pthread_mutex_lock(th->rt->mtx + MTX_SYNC);
	pthread_mutex_unlock(th->rt->mtx + MTX_SYNC);
	puts("whu");
}
