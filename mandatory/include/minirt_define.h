#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

// defines and enums

# define WIN_HEIGHT 810
# define WIN_WIDTH 1440

# define CUST_ERR_AMOUNT 2

// ERR_RTRN is a fix option (for errn_set()),
// the custom errors are -2 and below.
enum	custom_error
{
	ERR_RTRN = -1,
	CERROR1 = -2,
	CERROR2 = -3
};

#endif