#include "../include/minirt_param.h"

t_short	errn_set(const t_short num)
{
	static t_short	saved_errnum;

	if (saved_errnum != ENOMEM && num != ERR_RTRN)
		saved_errnum = num;
	return (saved_errnum);
}
