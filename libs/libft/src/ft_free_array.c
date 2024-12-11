/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:37:34 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:38:07 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// free all pointers in array, then array itself. Array must be NULL-terminated.
void	ft_free_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i] != NULL)
			free(array[i++]);
		free(array);
	}
}
