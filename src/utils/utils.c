#include <MLX42/MLX42.h>
#include <scene.h>
#include <utils.h>
#include <RTmlx.h>

t_cint32	cleanup(t_rt *rt)
{
	if (THREADS > 1)
	{
		// Wat gebeurt er bij mutex SYNC?
		// toggle_bool(rt->mtx + MTX_QUIT_ROUTINE, &rt->quit_routine, true);
		if (rt->mtx_init_check == true)
		{
			pthread_mutex_unlock(rt->mtx + MTX_SYNC);
			destroy_mutexes(rt, MTX_AMOUNT);
		}
		if (rt->thread_creation_check == true)
			destroy_threads(rt, THREADS - 1);
		if (rt->read_scene->objs)
			free(rt->read_scene->objs);
		if (rt->read_scene->lights)
			free(rt->read_scene->lights);
	}
	else if (rt->win->img != NULL)
		mlx_delete_image(rt->win->mlx, rt->win->img);
	if (rt->win->mlx != NULL)
		mlx_terminate(rt->win->mlx);
	if (rt->scene->objs)
		free(rt->scene->objs);
	if (rt->scene->lights)
		free(rt->scene->lights);
	return (rt->errnum);
}

/**
 * @brief Broadcasts scalar value to all four indexes of the t_vec4.
 * @param scalar Value to broadcast to vector[X, Y, Z, W].
 * @return (t_vec4){scalar, scalar, scalar, scalar}
 */
t_vec4	bcast4(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, scalar});
}

/**
 * @brief Broadcasts scalar value to first three indexes of the t_vec4.
 * @param scalar Value to broadcast to vector[X, Y, Z].
 * @return (t_vec4){scalar, scalar, scalar, 1.0f}
 */
t_vec4	bcast3(float scalar)
{
	return ((t_vec4){scalar, scalar, scalar, 1.0F});
}

// Clamp a value between min and max
float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

// Clamp a vector between min and max
t_vec4	vec_clamp(t_vec4 value, float min, float max)
{
	return (t_vec4)
	{
		clamp(value[0], min, max),
		clamp(value[1], min, max),
		clamp(value[2], min, max),
		clamp(value[3], min, max)
	};
}

int32_t	r_down(float value)
{
	return ((int32_t)(value - 0.5));
}
