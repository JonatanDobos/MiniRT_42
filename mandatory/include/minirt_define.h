#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

// defines and enums

# define WIN_HEIGHT 810
# define WIN_WIDTH 1440

# define CUST_ERR_AMOUNT 2

/**
 * @brief Custom error code (range: <= -2) macros.
 * @param ERR_RTRN A fixed option (for err_set()).
 * @param CERROR1 Custom error code 1.
 * @param CERROR2 Custom error code 2.
 */
enum	custom_error
{
	ERR_RTRN = -1,
	CERROR1 = -2,
	CERROR2 = -3
};

#endif
