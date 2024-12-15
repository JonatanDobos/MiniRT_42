#include "../include/minirt_param.h"

static void	close_mlx(void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	exit_clean(m, errset(ERTRN));
}

static void	key_mlx(mlx_key_data_t key, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	if (key.key == MLX_KEY_ESCAPE)
		return (close_mlx(m));
}

static void	resize_mlx(int32_t nhght, int32_t nwdth, void *param)
{
	t_minirt	*m;

	m = (t_minirt *)param;
	if (mlx_resize_image(m->win.img, nwdth, nhght) == false)
		exit_clean(m, perrmlx("resize_mlx", mlx_errno));
	m->win.pixels = m->win.img->pixels;
	m->win.ratio_w = (float)nwdth / (float)nhght;
	if ((t_uin16)nhght < m->win.rndr_hght)
		m->win.rndr_hght = nhght;
	m->win.rndr_wdth = (float)m->win.rndr_hght * m->win.ratio_w;
}

void	init_hooks(t_minirt *m)
{
	mlx_close_hook(m->win.mlx, close_mlx, m);
	mlx_key_hook(m->win.mlx, key_mlx, m);
	mlx_resize_hook(m->win.mlx, resize_mlx, m);
}
