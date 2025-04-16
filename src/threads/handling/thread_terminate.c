#include <libft.h>
#include <stdio.h>
#include <miniRT.h>
#define MTX_FAIL "pthread_mutex_destroy() failed on index "

void	destroy_mutexes(t_rt *rt, size_t amount)
{
	char	on_err[sizeof(MTX_FAIL) + 12];
	ssize_t	i;

	i = amount - 1;
	while (i != -1)
	{
		if (pthread_mutex_destroy(rt->mtx + i) != 0)
		{
			if (i > 0)
			{
				cpy_str(on_err, MTX_FAIL);
				nbr_to_buff(on_err + sizeof(MTX_FAIL) - 1, (int64_t)i);
				pthread_mutex_lock(rt->mtx + MTX_PRINT);
				perror(on_err);
				pthread_mutex_unlock(rt->mtx + MTX_PRINT);
			}
		}
		--i;
	}
}

bool	destroy_conditions(t_rt *rt)
{
	if (pthread_cond_destroy(&rt->cond) != 0)
	{
		perror("pthread_cond_destroy");
		return (false);
	}
	return (true);
}

void	destroy_threads(t_rt *rt)
{
	if (pthread_join(rt->thread.thread, NULL) != 0)
	{
		pthread_mutex_lock(rt->mtx + MTX_PRINT);
		perror("pthread_cond_destroy");
		pthread_mutex_unlock(rt->mtx + MTX_PRINT);
	}
}
