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

int	*group_numbers(const char prefix)
{
	static int	groups[6][5] = {
		{1, 3, 0, 0, 0},	// 'A'
		{3, 3, 1, 0, 0},	// 'C'
		{3, 1, 3, 0, 0},	// 'L'
		{3, 1, 3, 0, 0},	// 'sp'
		{3, 3, 3, 0, 0},	// 'pl'
		{3, 3, 1, 1, 3}		// 'cy'
	};
	return (groups[find_char("ACLspcy", prefix)]);
}

bool	one_member_group(char **line)
{
	char	*tmp;
	
	tmp = *line;
	tmp += skip_signed_digits(tmp);
	if (*tmp == '.')
	{
		++tmp;
		if (ft_isnum(tmp) == true)
			tmp += skip_signed_digits(tmp);
		else
			return (false);
	}
	*line = tmp;
	return (true);
}

bool	three_member_group(char **line)
{
	uint8_t iterate_twice;
	char	*tmp;
	
	tmp = *line;
	tmp += skip_signed_digits(tmp);
	iterate_twice = 0;
	while (iterate_twice < 2)
	{
		if (one_member_group(&tmp) == false)
			return (false);
		if (tmp[0] == ',' && tmp[1] != '.')
			++tmp;
		else
			return (false);
		if (tmp[0] == '\0' || tmp[0] == '\n')
			return (false);
		++iterate_twice;
	}
	if (one_member_group(&tmp) == false)
		return (false);
	*line = tmp;
	return (true);
}

bool	check_line(char *line, const char prefix, uint8_t nbr_of_groups)
{
	uint8_t		group_index;
	const int	*prefix_nbr = group_numbers(prefix);
	static bool	(*group_ptr[2])(char **) = {
		one_member_group,
		three_member_group
	};

	group_index = 0;
	while (*line != '\0' && *line != '#')
	{
		if (ft_isnum(line) == false)
			return (false);
		if (group_ptr[((*prefix_nbr) == 3)](&line) == false)
			return (false);
		++group_index;
		if (group_index > nbr_of_groups)
			return (false);
		++prefix_nbr;
		line += skip_spaces(line);
	}
	if (group_index != nbr_of_groups)
		return (false);
	return (true);
}

/**
 * Each prefix corresponds to a specific number of groups of numbers:
 * "A "  -> 2 groups: ambient light ratio and RGB color
 * "C "  -> 3 groups: position, orientation, and field of view
 * "L "  -> 3 groups: position, brightness, and RGB color
 * "sp " -> 3 groups: position, diameter, and RGB color
 * "pl " -> 3 groups: position, normal vector, and RGB color
 * "cy " -> 5 groups: position, orientation, diameter, height, and RGB color
 * The function returns:
 * - 2 for "A "
 * - 3 for "C ", "L ", "sp ", and "pl "
 * - 5 for "cy "
 * - 0 if no valid prefix is found
 */
static uint8_t	is_valid_prefix(const char *line, char *prefix)
{
	const char		*prefixes[6] = {"A", "C", "L", "sp", "pl", "cy"};
	const size_t	num_prefixes = sizeof(prefixes) / sizeof(*prefixes);
	const uint8_t	nbr_of_groups[6] = {2, 3, 3, 3, 3, 5};
	size_t			prefix_len;
	size_t			i;

	i = 0;
	while (i < num_prefixes)
	{
		prefix_len = ft_strlen(prefixes[i]);
		if (ft_strncmp(line, prefixes[i], prefix_len) == 0 &&
			ft_isspace(line[prefix_len]) == true)
		{
			if (ft_isspace(line[prefix_len - 1]) == false)
			{
				*prefix = *line;
				return (nbr_of_groups[i]);
			}
		}
		++i;
	}
	return (false);
}

static int16_t	check_characters(char *line)
{
	uint8_t	nbr_of_groups;
	size_t	i;
	char	prefix;

	nbr_of_groups = is_valid_prefix(line, &prefix);
	if (nbr_of_groups == false)
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_2)));
	i = 2 + ft_isspace(line[2]);
	i += skip_spaces(line + i);
	if (check_line(line + i, prefix, nbr_of_groups) == false)
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_3)));
	return (EXIT_SUCCESS);
}

static int16_t	input_line_check(char *line)
{
	const size_t	len = ft_strlen(line);

	if (*line == '\n' || *line == '#')
		return (EXIT_SUCCESS);
	if (len < 4)
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_1)));
	if (check_characters(line) != EXIT_SUCCESS)
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
