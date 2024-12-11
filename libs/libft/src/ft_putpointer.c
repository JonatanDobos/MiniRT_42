/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putpointer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:45:45 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:46:23 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putpointer(unsigned long p)
{
	int	len;

	len = 0;
	len += ft_putstr("0x");
	len += ft_putnbr_base(p, "0123456789abcdef");
	return (len);
}
