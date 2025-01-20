#include <stdlib.h>
#include <miniRT.h>
#include <parsing.h>
#include <scene.h>
#include <RTmlx.h>
#include <utils.h>

bool	check_input(t_rt *rt, int argc, char **argv)
{
	(void)rt;
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

void	init_main(t_rt *rt, t_scene *scn, t_window *win)
{
	ft_bzero(rt, sizeof(t_rt));
	ft_bzero(scn, sizeof(t_scene));
	ft_bzero(win, sizeof(t_window));
	errset((int64_t)rt->errnum);
	rt->scene = scn;
	rt->win = win;

}
int main(int argc, char **argv)
{
	t_rt		rt;
	t_scene		sc;
	t_window	win;

	printf("miniRT startwatch %f\n", mlx_get_time());
	init_main(&rt, &sc, &win);
	if (check_input(&rt, argc, argv) == EXIT_FAILURE || \
		input_parse(&rt, argv[1]) != 0 || \
		windows_setup_mlx(&rt) == EXIT_FAILURE)
	{
		return (perr("Parsing", errset(ERTRN)), cleanup(&rt));
	}
	render_scene(&rt, rt.scene);

	printf("%f\n", mlx_get_time());

	mlx_loop(rt.win->mlx); // Start the MLX loop
	// mlx_run_time()
	cleanup(&rt);
	printf("exiting miniRT\n");
	return (EXIT_SUCCESS);
}


// typedef float				t_fvec __attribute__ ((vector_size (4 * sizeof(float))));
// bool	parse_vector(char **linep, t_fvec *vector, bool normalized)
// {
// 	char	*line;
// 	float	vals[3];
// 	float	min;
// 	float	max;

// 	line = *linep;
	
// 	min = 0;
// 	max = 0;
// 	if (normalized)
// 	{
// 		min = -1.0f;
// 		max = +1.0f;
// 	}
// 	if (!parse_float(&line, vals + X, min, max) || *line++ != ',')
// 		return (false);
// 	if (!parse_float(&line, vals + Y, min, max) || *line++ != ',')
// 		return (false);
// 	if (!parse_float(&line, vals + Z, min, max))
// 		return (false);
// 	*vector = (t_fvec){vals[X], vals[Y], vals[Z]};
// 	*linep = line;
// 	return (!normalized || is_normalized(*vector));