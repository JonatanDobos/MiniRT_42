#include "../include/minirt_param.h"

/**
 * @brief overwrites *(address) to errnum.
 * @param errnum New error code, ERTRN, ESET, or new address.
 * @return shared_errnum if accessible.
 * @return CERRNSET (-3) when trying to access unset address.
 * @return ESET (-2) when waiting for new address.
 * @note This function saves a given address (input at first call).
 * @note *(address) is used to save given errnum.
 * @note Advantage: no ptr parameter needed.
 * @note Advantage: *(address) still reachable outside of function.
 * @note Use ERTRN (-1) to return last errnum without overwriting.
 * @note Use ESET (-2) to set the shared_errnum address in the next call.
 */
t_long	errset(const t_long errnum)
{
	static t_long	*shared_errnum = NULL;
	static bool		set_address = true;

	if (set_address == true)
	{
		if (errnum >= 0 || errnum < -2)
		{
			shared_errnum = errnum;
			set_address = false;
			return (errnum);
		}
		return (ESET);
	}
	if (shared_errnum != NULL && errnum != ESET)
	{
		if (*shared_errnum != ENOMEM && errnum != ERTRN)
			*shared_errnum = errnum;
		return (*shared_errnum);
	}
	else if (errnum == ESET)
		return (set_address = true, ESET);
	return (CERRNSET);
}

/**
 * @brief Saves errnum inside static variable.
 * @param errnum Error code to be saved, or ERTRN (-1).
 * @return saved errnum.
 * @note If errnum == ERTRN (-1) it returns last errnum without saving.
 */
t_short	errsave(const t_short errnum)
{
	static t_short	saved_errnum;

	if (saved_errnum != ENOMEM && errnum != ERTRN)
		saved_errnum = errnum;
	return (saved_errnum);
}
