#include <RTerror.h>
#include <string.h>
#include <libft.h>
#include <MLX42/MLX42.h>

static void	perr_custom(const int16_t errnum)
{
	const int16_t	index = (errnum * -1) - 2;
	const char		msg[CUST_ERR_AMOUNT][30] = \
		{
			"Waiting for errnum address",
			"Errnum address not set",
			"Wrong format",
			"Wrong file extension"
		};

	if (index >= 0 && index < CUST_ERR_AMOUNT)
		ft_putstr_fd(msg[index], STDERR_FILENO);
	else
		ft_putstr_fd("Unknown error!", STDERR_FILENO);
}

/**
 * @brief Prints error message.
 * @param place Name of the function the error occured in/ got caught in.
 * @param errnum Error code.
 * @return errnum
 */
int16_t	perr(char *place, const int16_t errnum)
{
	if (errnum == 0)
		return (errnum);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd("miniRT: ", STDERR_FILENO);
	if (place != NULL)
	{
		ft_putstr_fd(place, STDERR_FILENO);
		ft_putstr_fd("(): ", STDERR_FILENO);
	}
	if (errnum < 0)
		perr_custom(errnum);
	else
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (errnum);
}

/**
 * @brief Prints error message followed by an additional message.
 * @param place Name of the function the error occured in/ got caught in.
 * @param errnum Error code.
 * @param msg Message following the error message.
 * @return errnum
 */
int16_t	perr_msg(char *place, const int16_t errnum, char *msg)
{
	perr(place, errnum);
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (errnum);
}

/**
 * @brief Prints error message based on mlx_errno.
 * @param place Name of the function the error occured in/ got caught in.
 * @param errnum Mlx error code.
 * @return errnum
 */
int16_t	perrmlx(char *place, const int16_t errnum)
{
	ft_putstr_fd("miniRT: ", STDERR_FILENO);
	if (place)
	{
		ft_putstr_fd(place, STDERR_FILENO);
		ft_putstr_fd("(): ", STDERR_FILENO);
	}
	ft_putstr_fd(mlx_strerror(errnum), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (errnum);
}
