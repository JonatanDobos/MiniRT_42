#include <scene.h>
#include <RTmlx.h>
#include <render.h>

void	res_downscale(t_rt *rt)
{
	float	perc;

	rt->win->res_ratio += RES_STEP_SIZE;
	if (rt->win->res_ratio > RES_RATIO_MAX)
		rt->win->res_ratio = RES_RATIO_MAX;
	rt->win->rndr_hght = (float)rt->win->mlx->height / rt->win->res_ratio;
	rt->win->rndr_wdth = (float)rt->win->mlx->width / rt->win->res_ratio;
	rt->scene->render = true;

	perc = (1.0f / rt->win->res_ratio) * 100;
	printf("\033[0;34m DOWNSCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		perc, rt->win->rndr_wdth, rt->win->rndr_hght, rt->win->mlx->width, rt->win->mlx->height);
}

void	res_upscale(t_rt *rt)
{
	float	perc;

	rt->win->res_ratio -= RES_STEP_SIZE;
	if (rt->win->res_ratio < 1.0f)
		rt->win->res_ratio = 1.0;
	rt->win->rndr_hght = (float)rt->win->mlx->height / rt->win->res_ratio;
	rt->win->rndr_wdth = (float)rt->win->mlx->width / rt->win->res_ratio;
	rt->scene->render = true;

	perc = (1.0f / rt->win->res_ratio) * 100;
	printf("\033[0;34m UPSCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		perc, rt->win->rndr_wdth, rt->win->rndr_hght, rt->win->mlx->width, rt->win->mlx->height);
}

void	res_rescale(t_rt *rt)
{
	float	perc;

	rt->win->rndr_hght = (float)rt->win->mlx->height / rt->win->res_ratio;
	rt->win->rndr_wdth = (float)rt->win->mlx->width / rt->win->res_ratio;
	rt->scene->render = true;

	perc = (1.0f / rt->win->res_ratio) * 100;
	printf("\033[0;34m RESCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		perc, rt->win->rndr_wdth, rt->win->rndr_hght, rt->win->mlx->width, rt->win->mlx->height);
}
