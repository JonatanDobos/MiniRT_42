#include <scene.h>
#include <utils.h>

t_cint32	cleanup(t_rt *rt, t_cint32 status)
{
	if (rt->img != NULL)
		mlx_delete_image(rt->mlx, rt->img);
	if (rt->mlx != NULL)
		mlx_terminate(rt->mlx);
	if (rt->scene->objarr)
		free(rt->scene->objarr);
	return (status);
}