/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc_array.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:46:41 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:46:42 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_realloc_array(char **array, size_t size)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (new == NULL)
		return (NULL);
	new[size] = NULL;
	while (size--)
	{
		new[size] = array[size];
	}
	free(array);
	return (new);
}
