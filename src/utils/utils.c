#include <MLX42/MLX42.h>
#include <scene.h>
#include <utils.h>
#include <RTmlx.h>

t_cint32	cleanup(t_rt *rt)
{
	if (rt->win->img != NULL)
		mlx_delete_image(rt->win->mlx, rt->win->img);
	if (rt->win->mlx != NULL)
		mlx_terminate(rt->win->mlx);
	if (rt->scene->objarr)
		free(rt->scene->objarr);
	return (rt->errnum);
}