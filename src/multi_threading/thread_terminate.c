#include <miniRT.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <threadsRT.h>
#include <render.h>
#include <libft.h>


void	destroy_mutexes(t_rt *rt, size_t amount)
{
	ssize_t	i;

	i = amount - 1;
	while (i != -1)
	{
		if (pthread_mutex_destroy(rt->mtx + i) != 0)
		{
			if (i == 1) {
				// pthread_mutex_lock(rt->mtx + MTX_SYNC);
				if (pthread_mutex_trylock(rt->mtx + MTX_SYNC) == EBUSY) {
					puts("locked");
					printf("errno %d\n", errno);
				} else {
					puts("now locked");
				}
			}
				// pthread_mutex_unlock(rt->mtx + MTX_SYNC);
			// if (i > 0)
			// {
				// pthread_mutex_lock(rt->mtx + MTX_PRINT);
				printf("%zu\n", i);
				perror("huh");
				write(STDERR_FILENO, "1pthread_mutex_destroy: Failed\n", 31);	//	also this write does need lock protection
				// pthread_mutex_unlock(rt->mtx + MTX_PRINT);
			// }
			// else
			// 	write(STDERR_FILENO, "2pthread_mutex_destroy: Failed\n", 31);	//	also this write does need lock protection
		}
		--i;
	}
}

bool	destroy_conditions(t_rt *rt)
{
	if (pthread_cond_destroy(&rt->cond) != 0)
	{
		write(STDERR_FILENO, "pthread_cond_destroy\n", 21);
		return (false);
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
}
