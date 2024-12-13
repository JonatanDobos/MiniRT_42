#include "../include/minirt_param.h"

void	render_loop(t_minirt *mrt)
{
	// rendering
}

void	init_struct(t_minirt *mrt)
{
	mrt->errnum = 0;
	mrt->win.hght = WIN_HEIGHT;
	mrt->win.wdth = WIN_WIDTH;
	mrt->win.id = 0;
	mrt->win.img = NULL;
	mrt->win.inst = NULL;
	mrt->win.resize = true;
}

int	main(int argc, char **argv)
{
	t_minirt	mrt;

	if (argc != 2)
		return (perr("main()", EINVAL));
	errn_set(0);
	init_struct(&mrt);
	if (input_parse(&mrt, argv[1]))
		return (errn_set(ERR_RTRN));
	if (window_init(&mrt.win, "miniRT"))
		return (errn_set(ERR_RTRN));
	render_loop(&mrt);
	return (errn_set(ERR_RTRN));
}
