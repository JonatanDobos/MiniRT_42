/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:38:57 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:39:00 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isascii(const int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}