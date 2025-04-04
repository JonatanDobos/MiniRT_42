#include <parsing.h>
// #include <utils.h>

//	Static Functions
static uint8_t	is_valid_prefix(char *line, char *prefix);

int16_t	line_validation(char *line)
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
