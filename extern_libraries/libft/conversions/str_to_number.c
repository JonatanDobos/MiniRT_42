/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_to_number.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:08 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:38:13 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
int		ft_atoi(t_cchr *nptr);
int		atoi_safe(t_cchr *nptr);
t_ll	ft_atoll(t_cchr *nptr);
t_ll	atoll_safe(t_cchr *nptr);

/*
	For all functions the MIN of all of them overflower, e.g.
	2147483648 overflows to -2147483648, because INT_MAX = 2147483647

	and it overflows again when "i * flag",
	-2147483648 * -1 = 2147483648, but it's bigger than INT_MAX,
	so it overflows back to -2147483648.
*/

int	ft_atoi(t_cchr *nptr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	if (*nptr == '\0')
		return (0);
	while (ft_isspace(*nptr) == 1)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

int	atoi_safe(t_cchr *nptr)
{
	int	i;
	int	flag;

	if (str0_ok(nptr) == false)
		return (0);
	i = 0;
	flag = 1;
	while (ft_isspace(*nptr) == 1)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

t_ll	ft_atoll(t_cchr *nptr)
{
	t_ll	i;
	int		flag;

	if (*nptr == '\0')
		return (0);
	i = 0;
	flag = 1;
	while (ft_isspace(*nptr) == 1)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}

t_ll	atoll_safe(t_cchr *nptr)
{
	t_ll	i;
	int		flag;

	if (str0_ok(nptr) == false)
		return (0);
	i = 0;
	flag = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			flag *= -1;
	while (*nptr >= '0' && *nptr <= '9')
		i = i * 10 + (*nptr++ - '0');
	return (i * flag);
}
