#include "../include/minirt_param.h"

/**
 * @brief Saves errnum inside static variable.
 * @param errnum Error code to be saved, or ERR_RTRN (-1).
 * @return saved errnum
 * @note If errnum == ERR_RTRN (-1) it returns last errnum without saving.
 */
t_short	err_set(const t_short errnum)
{
	static t_short	saved_errnum;

	if (saved_errnum != ENOMEM && errnum != ERR_RTRN)
		saved_errnum = errnum;
	return (saved_errnum);
}
