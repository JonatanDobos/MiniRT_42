#include <scene.h>
#include <RTmlx.h>
#include <render.h>

bool	res_downscale(t_window *win)
{
	float	perc;

	win->res_ratio += RES_STEP_SIZE;
	if (win->res_ratio > RES_RATIO_MAX)
		win->res_ratio = RES_RATIO_MAX;
	win->rndr_hght = (float)win->mlx->height / win->res_ratio;
	win->rndr_wdth = (float)win->mlx->width / win->res_ratio;

	perc = (1.0F / win->res_ratio) * 100;
	printf("\033[0;34m DOWNSCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		perc, win->rndr_wdth, win->rndr_hght, win->mlx->width, win->mlx->height);
		return (true);
}

bool	res_upscale(t_window *win)
{
	float	perc;

	win->res_ratio -= RES_STEP_SIZE;
	if (win->res_ratio < 1.0F)
		win->res_ratio = 1.0F;
	win->rndr_hght = (float)win->mlx->height / win->res_ratio;
	win->rndr_wdth = (float)win->mlx->width / win->res_ratio;

	perc = (1.0F / win->res_ratio) * 100.0F;
	// printf("\033[0;34m UPSCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		// perc, win->rndr_wdth, win->rndr_hght, win->mlx->width, win->mlx->height);
	return (true);
}

bool	res_setscale(t_window *win, const float scale)
{
	float	perc;

	win->res_ratio = scale;
	if (win->res_ratio < 1.0F)
		win->res_ratio = 1.0F;
	win->rndr_hght = (float)win->mlx->height / win->res_ratio;
	win->rndr_wdth = (float)win->mlx->width / win->res_ratio;
	perc = (1.0F / win->res_ratio) * 100.0F;
	// printf("\033[0;34m SET SCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		// perc, win->rndr_wdth, win->rndr_hght, win->mlx->width, win->mlx->height);
	return (true);
}
