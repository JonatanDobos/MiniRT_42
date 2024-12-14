#include "../include/minirt_param.h"

t_short	input_parse(t_minirt *mrt, const char *file)
{
	const int	fd = open(file, O_RDONLY);

	if (fd < 0)
		return (errset(perr("input_parse", errno)));
	(void)mrt;
	return (SUCCESS);
}
