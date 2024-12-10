/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr_null.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:47:26 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:47:28 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strchr_null(const char *str, char c)
{
	int	i;

	i = 0;
	if (str)
		while (str[i] || str[i] == c)
			if (str[i++] == c)
				return (i);
	return (0);
}
