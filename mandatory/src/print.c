#include "../include/minirt_param.h"

static t_short	perr_custom(char *place, const t_short num)
{
	const t_short	index = (num * -1) - 2;

	const char	msg[CUST_ERR_AMOUNT][20] = \
		{"Custom error 1", "Custom error 2"};

	ft_putstr_fd("miniRT: ", STDERR_FILENO);
	if (place)
	{
		ft_putstr_fd(place, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (index >= 0 && index < CUST_ERR_AMOUNT)
		ft_putstr_fd(msg[index], STDERR_FILENO);
	else
		ft_putstr_fd("!unknown error!", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (num);
}

// Prints out:
// "miniRT: [*place](name of function): [strerror(num)]"
t_short	perr(char *place, const t_short num)
{
	if (num < 0)
		return (perr_custom(place, num));
	ft_putstr_fd("miniRT: ", STDERR_FILENO);
	if (place)
	{
		ft_putstr_fd(place, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(strerror(num), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (num);
}

t_short	perrmlx(char *place, const t_short num)
{
	ft_putstr_fd("miniRT: ", STDERR_FILENO);
	if (place)
	{
		ft_putstr_fd(place, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(mlx_strerror(num), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (num);
}
