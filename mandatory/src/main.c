#include "../include/minirt_param.h"

void	render_loop(t_minirt *m)
{
	init_hooks(m);
	mlx_loop(m->win.mlx);
}

int	main(int argc, char **argv)
{
	t_minirt	m;

	if (argc != 2)
		return (perr("main", EINVAL));
	errset((int64_t)&m.errnum);
	init_struct_m(&m);
	if (input_parse(&m, argv[1]))
		return (m.errnum);
	_print_parsing(&m.scene);//t
	if (window_init(&m.win, m.win.window_wdth, m.win.window_hght, "miniRT"))
		return (clean_all(&m), m.errnum);
	render_loop(&m);
	clean_all(&m);
	return (m.errnum);
}
