#include "../include/minirt_param.h"

/**
 * @brief Cleans all variables used by program and exits with errnum.
 * @param mrt Pointer to t_minirt struct to be cleaned.
 * @param errnum Error code to exit with.
 */
void	exit_clean(t_minirt *mrt, t_short errnum)
{
	clean_all(mrt);
	exit(errnum);
}
