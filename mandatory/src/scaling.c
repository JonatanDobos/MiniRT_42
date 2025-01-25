#include "../include/minirt_param.h"

void	scaled_res_set_pixel(t_window *w, t_uin16 x, t_uin16 y, t_vec4 color)
{
	const t_vec4	to_rgba = {255.0f, 255.0f, 255.0f, 255.0f};
	t_uint8			*pixels;
	t_axis2			i;
	t_axis2			pixel;

	color *= to_rgba;
	i.y = 0;
	while (i.y < (t_uin16)w->res_ratio)
	{
		i.x = 0;
		pixel.y = y * (t_uin16)w->res_ratio + i.y;
		while (i.x < (t_uin16)w->res_ratio)
		{
			pixel.x = x * (t_uin16)w->res_ratio + i.x;
			if (pixel.x > w->mlx->width || pixel.y > w->mlx->height)
				continue ;
			pixels = w->pixels + (pixel.y * w->mlx->width + pixel.x) * 4;
			*(pixels++) = (t_uint8)color[R];
			*(pixels++) = (t_uint8)color[G];
			*(pixels++) = (t_uint8)color[B];
			*(pixels++) = (t_uint8)color[A];
			++i.x;
		}
		++i.y;
	}
}

void	res_downscale(t_minirt *m)
{
	float	perc;

	m->win.res_ratio += RES_STEP_SIZE;
	if (m->win.res_ratio > RES_RATIO_MAX)
		m->win.res_ratio = RES_RATIO_MAX;
	m->win.rndr_hght = (float)m->win.mlx->height / m->win.res_ratio;
	m->win.rndr_wdth = (float)m->win.mlx->width / m->win.res_ratio;
	m->scene.render = true;

	perc = (1.0f / m->win.res_ratio) * 100;
	printf("\033[0;34m DOWNSCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		perc, m->win.rndr_wdth, m->win.rndr_hght, m->win.mlx->width, m->win.mlx->height);
}

void	res_upscale(t_minirt *m)
{
	float	perc;

	m->win.res_ratio -= RES_STEP_SIZE;
	if (m->win.res_ratio < 1.0f)
		m->win.res_ratio = 1.0;
	m->win.rndr_hght = (float)m->win.mlx->height / m->win.res_ratio;
	m->win.rndr_wdth = (float)m->win.mlx->width / m->win.res_ratio;
	m->scene.render = true;

	perc = (1.0f / m->win.res_ratio) * 100;
	printf("\033[0;34m UPSCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		perc, m->win.rndr_wdth, m->win.rndr_hght, m->win.mlx->width, m->win.mlx->height);
}

void	res_rescale(t_minirt *m)
{
	float	perc;

	m->win.rndr_hght = (float)m->win.mlx->height / m->win.res_ratio;
	m->win.rndr_wdth = (float)m->win.mlx->width / m->win.res_ratio;
	m->scene.render = true;

	perc = (1.0f / m->win.res_ratio) * 100;
	printf("\033[0;34m RESCALE: %.0f%% (%dx%d) ~ (%dx%d)\033[0m\n",
		perc, m->win.rndr_wdth, m->win.rndr_hght, m->win.mlx->width, m->win.mlx->height);
}
