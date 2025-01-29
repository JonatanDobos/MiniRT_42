#include <math.h>
#include <utils.h>
#include <MLX42/MLX42.h>
#include <scene.h>
#include <RTmlx.h>
#include <sys/param.h>

void	scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color)
{
	const t_vec4	to_rgba = {255.0f, 255.0f, 255.0f, 255.0f};
	uint8_t			*pixels;
	t_axis2			i;
	t_axis2			pixel;

	color *= to_rgba;
	i.y = 0;
	while (i.y < (uint16_t)w->res_ratio)
	{
		i.x = 0;
		pixel.y = y * (uint16_t)w->res_ratio + i.y;
		while (i.x < (uint16_t)w->res_ratio)
		{
			pixel.x = x * (uint16_t)w->res_ratio + i.x;
			if (pixel.x > w->mlx->width || pixel.y > w->mlx->height)
				continue ;
			pixels = w->pixels + (pixel.y * w->mlx->width + pixel.x) * 4;
			*(pixels++) = (uint8_t)color[R];
			*(pixels++) = (uint8_t)color[G];
			*(pixels++) = (uint8_t)color[B];
			*(pixels++) = (uint8_t)color[A];
			++i.x;
		}
		++i.y;
	}
}

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
