#include <miniRT.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <threadsRT.h>
#include <render.h>
#include <libft.h>

bool	initialize_mutexes(t_rt *rt)
{
	size_t	i;

	i = 0;
	while (i < MTX_AMOUNT)
	{
		if (pthread_mutex_init(rt->mtx + i, NULL) != 0)
		{
			write(STDERR_FILENO, "pthread_mutex_init: Failed\n", 27);
			if (i > 0)
				destroy_mutexes(rt, i);
			return (false);
		}
		++i;
	}
	return (true);
}

bool	initialize_conditions(t_rt *rt)
{
	if (pthread_cond_init(&rt->cond_done_rend, NULL) != 0)
	{
		write(STDERR_FILENO, "pthread_cond_init\n", 18);
		return (false);
	}
	return (true);
}

bool	launch_pthreads(t_rt *rt)
{
	ssize_t	i;
	
	i = 0;
	pthread_mutex_lock(rt->mtx + MTX_SYNC);
	while (i < THREADS - 1)
	{
		rt->threads[i].rt = rt;
		rt->threads[i].scene = rt->scene;
		rt->threads[i].win = rt->win;
		rt->threads[i].id = i + 1;
		if (pthread_create(&rt->threads[i].thread, NULL, (t_cast)thread_routine_init, &rt->threads[i]) != 0)
		{
			pthread_mutex_lock(rt->mtx + MTX_PRINT);
			printf("pthread_create: philosophers\n");
			pthread_mutex_unlock(rt->mtx + MTX_PRINT);
			rt->thread_creation_check = false;
			pthread_mutex_unlock(rt->mtx + MTX_SYNC);
			if (i > 0)
				destroy_threads(rt, i);
			return (false);
		}
		++i;
	}
	return (true);
}