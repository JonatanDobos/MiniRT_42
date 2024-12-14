#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

// defines and enums

# define WIN_HEIGHT 810
# define WIN_WIDTH 1440

# define CUST_ERR_AMOUNT 2

/**
 * @brief Custom error code (range: <= -2) macros.
 * @param ERTRN A fixed option (errset() & errsave()).
 * @param ESET A fixed option (errset()).
 * @param CERRNSET Returned by errset() when static is NULL.
 * @param CERROR2 Custom error code 2.
 */
enum	custom_error
{
	ERTRN = -1,
	ESET = -2,
	CERRNSET = -3,
	CERROR2 = -4
};

#endif
