#include <miniRT.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <threadsRT.h>
#include <libft.h>

//	Static Functions
static bool	create_and_launch_mutex(t_rt *rt);

bool	init_pthread_mutex(t_rt *rt)
{
	if (create_and_launch_mutex(rt) == false)
		return (false);
	rt->threads = (t_thread *)malloc(sizeof(t_thread) * THREADS);
	if (rt->threads == NULL)
	{
		write(STDERR_FILENO, "malloc: Pthread creation failed\n", 32);
		destroy_mutexes(rt, MTX_AMOUNT);
		return (false);
	}
	return (true);
}

bool	launch_pthreads(t_rt *rt)
{
	ssize_t	i;

	i = 0;
	pthread_mutex_lock(rt->mtx + MTX_SYNC);
	while (i < THREADS)
	{
		if (pthread_create(&rt->threads[i].thread, NULL, (t_cast)my_screw_you_joni_render, rt) != 0)
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

void	destroy_threads(t_rt *rt, size_t thread_amount)
{
	size_t	i;

	i = 0;
	while (i < thread_amount)
	{
		if (pthread_join(rt->threads[i].thread, NULL) != 0)
		{
			pthread_mutex_lock(rt->mtx + MTX_PRINT);
			printf("pthread_join: Thread %zu failed.", i);
			pthread_mutex_unlock(rt->mtx + MTX_PRINT);
		}
		++i;
	}
	free_ptr(&rt->threads);
}

void	destroy_mutexes(t_rt *rt, size_t amount)
{
	ssize_t	i;

	i = amount - 1;
	while (i != -1)
	{
		if (pthread_mutex_destroy(rt->mtx + i) != 0)
		{
			if (i > 0)
			{
				pthread_mutex_lock(rt->mtx + MTX_PRINT);
				write(STDERR_FILENO, "pthread_mutex_destroy: Failed\n", 30);	//	also this write does need lock protection
				pthread_mutex_unlock(rt->mtx + MTX_PRINT);
			}
			else
				write(STDERR_FILENO, "pthread_mutex_destroy: Failed\n", 30);	//	also this write does need lock protection
		}
		--i;
	}
}

static bool	create_and_launch_mutex(t_rt *rt)
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