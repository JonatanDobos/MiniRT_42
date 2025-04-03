#include <MLX42/MLX42.h>
#include <parsing.h>
#include <scene.h>
#include <utils.h>
#include <RTmlx.h>
#include <RTerror.h>
#define NO_FILENAME "Give argument: ./miniRT <filename>\n"
#define SCREEN_ERROR "Screensize is too small\n"

int16_t setup_init_parsing(t_rt *rt, const int argc, const char *argv)
{
	if (argc != 2)
		return (write(1, NO_FILENAME, sizeof(NO_FILENAME) - 1), EXIT_FAILURE);
	else if (SCREEN_WIDTH < 5 || SCREEN_HEIGHT < 5)
		return (write(1, SCREEN_ERROR, sizeof(SCREEN_ERROR) - 1), EXIT_FAILURE);
	else if (read_inp_file(argv, rt->scene) != 0)
		return (cleanup(rt), errset(ERTRN));
	else if (windows_setup_mlx(rt) != 0)
		return (cleanup(rt), perr("MLX", errset(ERTRN)));
	rt->win->target_time += (float)(rt->scene->l_arr_size + rt->scene->o_arr_size) * 0.0005F;
	rt->win->target_time = clamp(rt->win->target_time, 0.01F, 0.025F);
	printf("TargetDTime: %f sec. | (%hu) fps\n", rt->win->target_time, (uint16_t)(1.0F / rt->win->target_time));//t
	return (EXIT_SUCCESS);
}

int32_t	cleanup(t_rt *rt)
{
	puts("cleanup start");//t
	if (THREADS > 1)
	{
		// Wat gebeurt er bij mutex SYNC?
		// toggle_bool(rt->mtx + MTX_QUIT_ROUTINE, &rt->quit_routine, true);
		if (rt->mtx_init_check == true)
		{
			pthread_mutex_unlock(rt->mtx + MTX_SYNC);
			destroy_mutexes(rt, MTX_AMOUNT);
		}
		if (rt->creation_check == true)
			destroy_threads(rt);
		if (rt->read_scene->objs)
			free(rt->read_scene->objs);
		if (rt->read_scene->lights)
			free(rt->read_scene->lights);
		if (rt->thread.img)
			rt->thread.img->pixels = rt->thread.pixels_mlx;
		if (rt->thread.pixels_own)
			free(rt->thread.pixels_own);
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

// Clamp a value between min and max
int	intclamp(int value, int min, int max)
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
