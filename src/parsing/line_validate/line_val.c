#include <parsing.h>

//	Static Functions
static int16_t	check_line_format(char *line);
static int16_t	process_format(char *line);
static uint8_t	is_valid_prefix(char *line, char *prefix);
static void		check_values(t_value_check *vc);

int16_t	line_validation(const int fd, t_scene *sc)
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
		if (line == NULL || check_line_format(skip_sp) != EXIT_SUCCESS
			|| input_type_parse(sc, &vc, skip_sp) != EXIT_SUCCESS)
			break ;
		free_str(&line);
	}
	free_str(&line);
	if (errset(ERTRN) == 0)
		check_values(&vc);
	return (errset(ERTRN));
}

static int16_t	check_line_format(char *line)
{
	const size_t	len = ft_strlen(line);

	if (*line == '\n' || *line == '#')
		return (EXIT_SUCCESS);
	if (len < 4)
		return (errset(perr_msg("input_line_check", ERRFORM, EMSG_1)));
	if (process_format(line) != EXIT_SUCCESS)
		return (errset(ERTRN));
	return (EXIT_SUCCESS);
}

static int16_t	process_format(char *line)
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
static uint8_t	is_valid_prefix(char *line, char *prefix)
{
	const char		*prefixes[6] = {"A", "C", "L", "sp", "pl", "cy"};
	const uint8_t	nbr_of_groups[6] = {2, 3, 3, 3, 3, 5};
	const size_t	num_prefixes = sizeof(prefixes) / sizeof(prefixes[0]);
	size_t			prefix_len;
	size_t			i;

	i = 0;
	while (i < num_prefixes)
	{
		prefix_len = ft_strlen(prefixes[i]);
		if (ft_strncmp(line, prefixes[i], prefix_len) == 0 && \
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

static void	check_values(t_value_check *vc)
{
	if (vc->amb_amount > 1)
		errset(perr_msg("check_values", ERRFORM, EMSG_4A));
	else if (vc->cam_amount != 1)
		errset(perr_msg("check_values", ERRFORM, EMSG_4C));
	else if (vc->obj_amount < 1)
		errset(perr_msg("check_values", ERRFORM, EMSG_4O));
}
