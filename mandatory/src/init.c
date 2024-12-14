#include "../include/minirt_param.h"

void	init_struct_mrt(t_minirt *mrt)
{
	ft_bzero(mrt, sizeof(t_minirt));
	mrt->win.resize = true;
	mrt->win.hght = WIN_HEIGHT;
	mrt->win.wdth = WIN_WIDTH;
}
