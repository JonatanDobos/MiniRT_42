#include "../include/minirt_param.h"

void	switch_bool(bool *value)
{
	if (*value == true)
		*value = false;
	else
		*value = true;
}

bool	cursor_inboud(mlx_t *mlx)
{
	t_int	x;
	t_int	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	return (x >= 0 && y >= 0 && x < mlx->width && y < mlx->height);
}

bool	axis2_inboud(t_axis2 val, t_axis2 xlim, t_axis2 ylim)
{
	return (val.x >= xlim.x && val.y >= ylim.x && val.x <= xlim.y && val.y <= ylim.y);
}
