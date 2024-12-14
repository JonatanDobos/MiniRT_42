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
	errset(0);
	init_struct_mrt(&mrt);
	if (input_parse(&mrt, argv[1]))
		return (errset(ERTRN));
	if (window_init(&mrt.win, "miniRT"))
		return (errset(ERTRN));
	render_loop(&mrt);
	clean_all(&mrt);
	return (errset(ERTRN));
}
