#include <scene.h>
#include <RTmlx.h>
#include <mathRT.h>
#include <render.h>

// void	set_pixel(t_window *win, uint16_t x, uint16_t y, t_vec4 color)
// {
// 	static const t_vec4	multiply = {255.0F, 255.0F, 255.0F, 255.0F};
// 	uint8_t				*pixels;

// 	color *= multiply;
// 	pixels = win->img->pixels + (y * win->window_wdth + x) * 4;
// 	*(pixels++) = (uint8_t)color[R];
// 	*(pixels++) = (uint8_t)color[G];
// 	*(pixels++) = (uint8_t)color[B];
// 	*(pixels++) = (uint8_t)color[A];
// }

void	scaled_res_set_pixel(t_window *w, uint16_t x, uint16_t y, t_vec4 color)
{
	static const t_vec4	to_rgba = {255.0F, 255.0F, 255.0F, 255.0F};
	uint8_t				*pixels;
	t_axis2				i;
	t_axis2				pixel;

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

void	set_pixel_multi(t_thread *th, uint16_t res_ratio, t_axis2 inp, t_vec4 color)
{
	static const t_vec4	to_rgba = {255.0F, 255.0F, 255.0F, 255.0F};
	uint8_t				*pixels;
	t_axis2				i;
	t_axis2				pix;

	color *= to_rgba;
	i.y = 0;
	while (i.y < res_ratio)
	{
		i.x = 0;
		pix.y = inp.y * res_ratio + i.y;
		while (i.x < res_ratio)
		{
			pix.x = inp.x * res_ratio + i.x;
			if (pix.x > th->img->width || pix.y > th->img->height)
				continue ;
			pixels = th->pixels + (pix.y * th->img->width + pix.x) * 4;
			*(pixels++) = (uint8_t)color[R];
			*(pixels++) = (uint8_t)color[G];
			*(pixels++) = (uint8_t)color[B];
			*(pixels++) = (uint8_t)color[A];
			++i.x;
		}
		++i.y;
	}
}
