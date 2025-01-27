#include "../include/minirt_param.h"

/**
 * @brief Cleans all variables used by program and exits with errnum.
 * @param m Pointer to t_minirt struct to be cleaned.
 * @param errnum Error code to exit with.
 */
void	exit_clean(t_minirt *m, int16_t errnum)
{
	clean_all(m);
	exit(errnum);
}
