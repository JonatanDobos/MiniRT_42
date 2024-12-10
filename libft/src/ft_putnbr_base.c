/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:45:27 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:45:29 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_base(long n, char *base)
{
	int			len;
	const int	size = ft_strlen(base);

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		n = -n;
	}
	if (n >= size)
		len += ft_putnbr_base(n / size, base);
	len += ft_putchar(base[n % size]);
	return (len);
}
