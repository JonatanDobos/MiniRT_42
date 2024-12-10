/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:38:39 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:38:42 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(const int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1 << 3);
	else
		return (0);
}
