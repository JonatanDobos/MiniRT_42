/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:39:30 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:39:32 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(const int c)
{
	if (c >= 32 && c <= 126)
		return (1 << 14);
	else
		return (0);
}