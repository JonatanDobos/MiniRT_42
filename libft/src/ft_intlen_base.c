/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:38:25 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:38:27 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_intlen_base(int n, char *base)
{
	int			len;
	const int	size = ft_strlen(base);

	len = 1;
	if (n < 0)
		len++;
	while (n >= size || n <= -size)
	{
		n = n / size;
		len++;
	}
	return (len);
}
