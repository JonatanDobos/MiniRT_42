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
	errset((t_long)&m.errnum);
	init_struct_m(&m);
	if (input_parse(&m, argv[1]))
		return (m.errnum);
	_print_parsing(&m.scene);//t
	if (window_init(&m.win, WIN_WIDTH, WIN_HEIGHT, "miniRT"))
		return (clean_all(&m), m.errnum);
	render_loop(&m);
	clean_all(&m);
	return (m.errnum);
}
