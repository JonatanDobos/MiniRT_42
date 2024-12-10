/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_toupper.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:47:15 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:47:17 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_str_toupper(char *src)
{
	const int	slen = ft_strlen(src);
	int			i;

	i = 0;
	while (i < slen)
	{
		src[i] = ft_toupper(src[i]);
		i++;
	}
	return (i);
}
