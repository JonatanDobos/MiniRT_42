#include "../include/minirt_param.h"

static void	close_mlx(void *param)
{
	t_minirt	*mrt;

	mrt = (t_minirt *)param;
	exit_clean(mrt, errset(ERTRN));
}

static void	key_mlx(mlx_key_data_t key, void *param)
{
	t_minirt	*mrt;

	mrt = (t_minirt *)param;
	if (key.key == MLX_KEY_ESCAPE)
		return (close_mlx(mrt));
}

void	init_hooks(t_minirt *mrt)
{
	mlx_close_hook(mrt->win.mlx, close_mlx, mrt);
	mlx_key_hook(mrt->win.mlx, key_mlx, mrt);
}
