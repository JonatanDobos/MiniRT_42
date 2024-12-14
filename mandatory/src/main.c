#include "../include/minirt_param.h"

void	render_loop(t_minirt *mrt)
{
	init_hooks(mrt);
	mlx_loop(mrt->win.mlx);
}

int	main(int argc, char **argv)
{
	t_minirt	mrt;

	if (argc != 2)
		return (perr("main", EINVAL));
	err_set(0);
	init_struct_mrt(&mrt);
	if (input_parse(&mrt, argv[1]))
		return (err_set(ERR_RTRN));
	if (window_init(&mrt.win, "miniRT"))
		return (err_set(ERR_RTRN));
	render_loop(&mrt);
	clean_all(&mrt);
	return (err_set(ERR_RTRN));
}
