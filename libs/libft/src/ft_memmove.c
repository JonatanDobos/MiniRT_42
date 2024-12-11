/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:42:45 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:42:46 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ucdest;
	const unsigned char	*ucsrc;

	if (!dest && !src)
		return (NULL);
	i = 0;
	ucdest = (unsigned char *)dest;
	ucsrc = (const unsigned char *)src;
	if (dest < src)
	{
		while (i < n)
		{
			ucdest[i] = ucsrc[i];
			i++;
		}
	}
	else
		while (n-- > 0)
			ucdest[n] = ucsrc[n];
	return (dest);
}
