#include "../include/minirt_param.h"

bool	switch_bool(bool *value)
{
	if (*value == true)
		return (*value = false, false);
	return (*value = true, true);
}

bool	cursor_inboud(mlx_t *mlx, uint16_t margin)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	return (x >= 0 + margin && y >= 0 + margin &&
			x < mlx->width - margin && y < mlx->height - margin);
}

bool	axis2_inboud(t_axis2 val, t_axis2 xlim, t_axis2 ylim)
{
	return (val.x >= xlim.x && val.y >= ylim.x && val.x <= xlim.y && val.y <= ylim.y);
}
