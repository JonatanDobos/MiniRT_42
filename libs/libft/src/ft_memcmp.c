/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:42:24 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:42:27 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	diff;

	while (n--)
	{
		diff = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (diff)
			return (diff);
	}
	return (0);
}
