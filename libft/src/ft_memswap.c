/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memswap.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:50:46 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:59:44 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memswap(void *a, void *b, size_t size)
{
	unsigned char	*temp;

	temp = (unsigned char *)malloc(size);
	if (temp == NULL)
		return (FAILURE);
	ft_memcpy(temp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, temp, size);
	free(temp);
	return (SUCCESS);
}
