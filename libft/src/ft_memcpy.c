/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:42:31 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:42:35 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ucdest;

	if (dest == NULL && src == NULL)
		return (NULL);
	ucdest = dest;
	while (n--)
		*ucdest++ = *(unsigned char *)src++;
	return (dest);
}
