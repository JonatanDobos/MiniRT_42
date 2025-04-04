#include <parsing.h>
#include <utils.h>

static void	check_values(t_value_check *vc)
{
	if (vc->amb_amount > 1)
		errset(perr_msg("check_values", ERRFORM, EMSG_4A));
	else if (vc->cam_amount != 1)
		errset(perr_msg("check_values", ERRFORM, EMSG_4C));
	// else if (vc->light_amount < 1)
	// 	errset(perr_msg("check_values", ERRFORM, EMSG_4L));
	else if (vc->obj_amount < 1)
		errset(perr_msg("check_values", ERRFORM, EMSG_4O));
}

static int16_t	input_line_check(char *line)
{
	const size_t	len = ft_strlen(line);

	if (*line == '\n' || *line == '#')
		return (EXIT_SUCCESS);
	if (len < 4)
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_1)));
	if (line_validation(line) != EXIT_SUCCESS)
		return (errset(ERTRN));
	return (EXIT_SUCCESS);
}

static int16_t	input_type_parse(t_scene *sc, t_value_check *vc, char *line)
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_amb(sc, vc, nxtv(line)));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_cam(sc, vc, nxtv(line)));
	if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(sc, vc, nxtv(line)));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_pl(sc, vc, nxtv(line)));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_sp(sc, vc, nxtv(line)));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_cy(sc, vc, nxtv(line)));
	return (EXIT_SUCCESS);
}

bool	init_dynarr(t_scene *sc)
{
	if (dynarr_create(&sc->obj_dynarr, 5, sizeof(t_objs)) == false)
		return (false);
	if (dynarr_create(&sc->light_dynarr, 5, sizeof(t_objs)) == false)
		return (false);
	return (true);
}

bool	shrink_dynarr(t_scene *sc)
{
	if (dynarr_shrink_to_fit(&sc->obj_dynarr) == false)
		return (false);
	if (dynarr_shrink_to_fit(&sc->light_dynarr) == false)
		return (false);
	return (true);
}



static int16_t	input_parse(const int fd, t_scene *sc)
{
	char			*skip_sp;
	char			*line;
	t_value_check	vc;

	ft_bzero(&vc, sizeof(t_value_check));
	while (true)
	{
		line = gnl(fd);
		if (line == NULL && errno == ENOMEM)
		{
			errset(perr("input_line_check", ENOMEM));
			break ;
		}
		if (line != NULL)
			skip_sp = line + skip_spaces(line);
		if (line == NULL || input_line_check(skip_sp) != EXIT_SUCCESS
			|| input_type_parse(sc, &vc, skip_sp) != EXIT_SUCCESS)
			break ;
		free_str(&line);
	}
	free_str(&line);
	if (errset(ERTRN) == 0)
		check_values(&vc);
	return (errset(ERTRN));
}

int16_t	read_inp_file(const char *file, t_scene *sc)
{
	const int		fd = open(file, O_RDONLY);

	if (fd < 0)
		return (errset(perr("input_parse", errno)));
	if (ft_strncmp(file + (ft_strlen(file) - 3), ".rt", 4) != 0)
		return (close(fd), errset(perr("input_parse", ERRFEXT)));
	if (init_dynarr(sc) == false)
		return (close(fd), errset(perr("read_inp_file", ENOMEM)));
	if (input_parse(fd, sc) != 0)
		return (close(fd), errset(ERTRN));
	if (shrink_dynarr(sc) == false)
		return (close(fd), errset(perr("read_inp_file", ENOMEM)));
	sc->objs = (t_objs *)dynarr_take_arr(&sc->obj_dynarr);
	sc->lights = (t_objs *)dynarr_take_arr(&sc->light_dynarr);
	close(fd);
	return (errset(ERTRN));
}
