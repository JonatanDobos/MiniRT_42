#include <parsing.h>
#include <utils.h>

static int16_t	check_values(t_value_check *vc)
{
	// if (vc->amb_amount != 1)
	// 	return (errset(perr_msg("check_values", ERRFORM, EMSG_4A)));
	// if (vc->cam_amount != 1)
	// 	return (errset(perr_msg("check_values", ERRFORM, EMSG_4C)));
	// if (vc->light_amount < 1)
	// 	return (errset(perr_msg("check_values", ERRFORM, EMSG_4L)));
	// if (vc->obj_amount < 1)
	// 	return (errset(perr_msg("check_values", ERRFORM, EMSG_4O)));
	return (EXIT_SUCCESS);
}

static bool	only_space_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!(ft_isspace(line[i]) || line[i] == '\n'))
			return (false);
		++i;
	}
	return (true);
}

static int16_t	check_characters(char *line)
{
	size_t	i;

	if (!(!ft_strncmp(line, "A", 1) && ft_isspace(line[1]))
		&& !(!ft_strncmp(line, "C ", 2) && ft_isspace(line[1]))
		&& !(!ft_strncmp(line, "L ", 2) && ft_isspace(line[1]))
		&& !(!ft_strncmp(line, "sp ", 3) && ft_isspace(line[2]))
		&& !(!ft_strncmp(line, "pl ", 3) && ft_isspace(line[2]))
		&& !(!ft_strncmp(line, "cy ", 3) && ft_isspace(line[2])))
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_2)));
	i = 2;
	while (ft_isspace(line[i]) || ft_isdigit(line[i]) || line[i] == '.'
		|| line[i] == ',' || line[i] == '-')
		++i;
	if (line[i] != '\0')
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_3)));
}

static int16_t	input_line_check(char *line)
{
	size_t			i;
	const size_t	len = ft_strlen(line);

	if ((len == 1 && line[0] == '\n') || only_space_line(line) == true)
		return (EXIT_SUCCESS);
	if (len < 4)
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_1)));
	if (check_characters != EXIT_SUCCESS)
		return (errset(ERTRN));
	return (EXIT_SUCCESS);
}

static int16_t	input_type_parse(t_scene *dest, t_value_check *vc, char *line)
{
	if (!ft_strncmp(line, "A", 1))
		return (parse_amb(dest, vc, nxtv(line)));
	if (!ft_strncmp(line, "C", 1))
		return (parse_cam(dest, vc, nxtv(line)));
	if (!ft_strncmp(line, "L", 1))
		return (parse_light(dest, vc, nxtv(line)));
	if (!ft_strncmp(line, "pl", 2))
		return (parse_pl(dest, vc, nxtv(line)));
	if (!ft_strncmp(line, "sp", 2))
		return (parse_sp(dest, vc, nxtv(line)));
	if (!ft_strncmp(line, "cy", 2))
		return (parse_cy(dest, vc, nxtv(line)));
	return (EXIT_SUCCESS);
}

int16_t	input_parse(t_rt *m, const char *file, t_scene *dest)
{
	const int		fd = open(file, O_RDONLY);
	char			*line;
	t_value_check	vc;

	if (fd < 0)
		return (errset(perr("input_parse", errno)));
	if (ft_strncmp(file + (ft_strlen(file) - 3), ".rt", 4))
		return (close(fd), errset(perr("input_parse", ERRFEXT)));
	ft_bzero(&vc, sizeof(t_value_check));
	dynarr_create(&dest->obj_dynarr, 5, sizeof(t_objs));
	dynarr_create(&dest->light_dynarr, 5, sizeof(t_objs));
	while (true)
	{
		line = gnl(fd);
		if (line == NULL && errno == ENOMEM)
			return (puts("1"), close(fd), errset(perr("input_line_check", errno)));
		if (line == NULL)
			break ;
		if (input_line_check(line) != EXIT_SUCCESS)
			return (puts("2"), close(fd), free_str(&line), errset(ERTRN));
		if (input_type_parse(dest, &vc, line) != EXIT_SUCCESS)
			return (puts("3"), close(fd), free_str(&line), errset(ERTRN));
		free_str(&line);
	}
	if (check_values(&vc) != EXIT_SUCCESS)
		return (close(fd), free_str(&line), errset(ERTRN));
	dynarr_shrink_to_fit(&dest->obj_dynarr);
	dynarr_shrink_to_fit(&dest->light_dynarr);
	dest->objs = (t_objs *)dynarr_take_arr(&dest->obj_dynarr);
	dest->lights = (t_objs *)dynarr_take_arr(&dest->light_dynarr);
	// _print_parsing(dest);//test
	return (close(fd), free_str(&line), EXIT_SUCCESS);
}
