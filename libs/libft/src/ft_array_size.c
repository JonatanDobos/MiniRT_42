/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_array_size.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:35:53 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:35:57 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_array_size(char **array)
{
	size_t	size;

	size = 0;
	if (!array)
		return (0);
	while (array[size])
		++size;
	return (size);
}
