/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stris.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:48:42 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:48:50 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// evaluate each character in string with func
// return evaluation value for first time func(c) != 0
int	ft_stris(const char *string, int (*func)(int c))
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (string[i])
	{
		check = func(string[i]);
		if (check == false)
			return (false);
		i++;
	}
	return (true);
}
