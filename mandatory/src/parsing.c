#include "../include/minirt_param.h"

static t_short	check_values(t_value_check *vc)
{
	if (vc->amb_amount != 1)
		return (errset(perr_msg("check_values", ERRFORM, EMSG_4A)));
	if (vc->cam_amount != 1)
		return (errset(perr_msg("check_values", ERRFORM, EMSG_4C)));
	if (vc->light_amount != 1)
		return (errset(perr_msg("check_values", ERRFORM, EMSG_4L)));
	if (vc->obj_amount < 1)
		return (errset(perr_msg("check_values", ERRFORM, EMSG_4O)));
	return (SUCCESS);
}

static t_short	input_line_check(char *line)
{
	size_t			i;
	const size_t	len = ft_strlen(line);

	if (len < 4)
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_1)));
	if (!(!ft_strncmp(line, "A", 1) && ft_iswhitespace(line[1]))
		&& !(!ft_strncmp(line, "C ", 2) && ft_iswhitespace(line[1]))
		&& !(!ft_strncmp(line, "L ", 2) && ft_iswhitespace(line[1]))
		&& !(!ft_strncmp(line, "sp ", 3) && ft_iswhitespace(line[2]))
		&& !(!ft_strncmp(line, "pl ", 3) && ft_iswhitespace(line[2]))
		&& !(!ft_strncmp(line, "cy ", 3) && ft_iswhitespace(line[2])))
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_2)));
	i = 2;
	while (ft_iswhitespace(line[i]) || ft_isdigit(line[i]) || line[i] == '.'
		|| line[i] == ',' || line[i] == '-')
		++i;
	if (line[i] != '\0')
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_3)));
	return (SUCCESS);
}

static t_short	input_type_parse(t_minirt *m, t_value_check *vc, char *line)
{
	if (!ft_strncmp(line, "A", 1))
		return (parse_amb(&m->scene, vc, skipws(line)));
	if (!ft_strncmp(line, "C", 1))
		return (parse_cam(&m->scene, vc, skipws(line)));
	if (!ft_strncmp(line, "L", 1))
		return (parse_light(&m->scene, vc, skipws(line)));
	if (!ft_strncmp(line, "pl", 2))
		return (parse_pl(&m->scene, vc, skipws(line)));
	if (!ft_strncmp(line, "sp", 2))
		return (parse_sp(&m->scene, vc, skipws(line)));
	if (!ft_strncmp(line, "cy", 2))
		return (parse_cy(&m->scene, vc, skipws(line)));
	return (SUCCESS);
}

t_short	input_parse(t_minirt *m, const char *file)
{
	const int		fd = open(file, O_RDONLY);
	char			*line;
	t_value_check	vc;

	if (fd < 0)
		return (errset(perr("input_parse", errno)));
	if (ft_strncmp(file + (ft_strlen(file) - 3), ".rt", 4))
		return (close(fd), errset(perr("input_parse", ERRFEXT)));
	ft_bzero(&vc, sizeof(t_value_check));
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (close(fd), errset(perr("input_line_check", errno)));
		if (input_line_check(line) != SUCCESS)
			return (close(fd), ft_free(&line), clean_all(m), errset(ERTRN));
		if (*line == '\0')
			break ;
		if (input_type_parse(m, &vc, line) != SUCCESS)
			return (close(fd), ft_free(&line), clean_all(m), errset(ERTRN));
		ft_free(&line);
	}
	if (check_values(&vc) != SUCCESS)
		return (close(fd), ft_free(&line), errset(ERTRN));
	return (close(fd), ft_free(&line), SUCCESS);
}
