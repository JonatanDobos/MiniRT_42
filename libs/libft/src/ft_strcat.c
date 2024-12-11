/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:47:21 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:47:23 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcat(char *dest, const char *src)
{
	const int	dlen = ft_strlen(dest);
	const int	slen = ft_strlen(src);
	int			i;

	i = 0;
	while (i < slen)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	return (i);
}
