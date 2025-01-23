#include <RTerror.h>

/**
 * @brief overwrites static *(address) to errnum.
 * @param errnum New error code, ERTRN, ESET, or new address.
 * @return *(address) if not NULL.
 * @return ERRNSET (-3) when trying to access unset address.
 * @return ESET (-2) when waiting for new address.
 * @note This function saves a given address (input at first call).
 * @note *(address) is used to save given errnum.
 * @note Advantage: no extra ptr parameter needed.
 * @note Advantage: *(address) still reachable outside of function.
 * @note Use ERTRN (-1) to return last errnum without overwriting.
 * @note Use ESET (-2) to set the shared_errnum address in the next call.
 */
int64_t	errset(const int64_t errnum)
{
	static int64_t	*shared_errnum = NULL;
	static bool		set_address = true;

	if (set_address == true)
	{
		if (errnum >= 0)
		{
			shared_errnum = (int64_t *)errnum;
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
	return (ERRNSET);
}

/**
 * @brief Saves num inside static variable saved_num.
 * @param errnum Number to be saved, or ERTRN (-1).
 * @return saved number.
 * @note Use ERTRN (-1) retreive saved_num without overwriting it.
 */
int16_t	nsave(const int16_t num)
{
	static int16_t	saved_num;

	if (saved_num != ENOMEM && num != ERTRN)
		saved_num = num;
	return (saved_num);
}
