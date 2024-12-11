#include "../include/minirt_param.h"

int	main(int argc, char **argv)
{
	if (argc != 1)
		return (FAILURE);
	write(STDOUT_FILENO, "Main\n", 5);
	return (SUCCESS);
}
