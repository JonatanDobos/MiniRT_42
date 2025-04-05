#include <MLX42/MLX42.h>
#include <parsing.h>
#include <scene.h>
#include <RTmlx.h>
#include <RTerror.h>
#include <mathRT.h>
#include <setup_clean.h>

int32_t	cleanup(t_rt *rt)
{
	if (THREADS > 1)
	{
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
