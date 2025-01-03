/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_to_unsigned_number.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:02 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:38:06 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
uint32_t	ato_ui(t_cchr *nptr);
uint32_t	ato_ui_safe(t_cchr *nptr);
t_ull		ato_t_ull(t_cchr *nptr);
t_ull		ato_t_ull_safe(t_cchr *nptr);

uint32_t	ato_ui(t_cchr *nptr)
{
	uint32_t	i;
	int			flag;

	if (*nptr == '\0')
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

uint32_t	ato_ui_safe(t_cchr *nptr)
{
	uint32_t	i;
	int			flag;

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

t_ull	ato_t_ull(t_cchr *nptr)
{
	t_ull	i;
	int		flag;

	if (*nptr == '\0')
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

t_ull	ato_t_ull_safe(t_cchr *nptr)
{
	t_ull	i;
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
