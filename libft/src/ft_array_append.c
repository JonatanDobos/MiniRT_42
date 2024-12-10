/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_array_append.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:36:08 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:36:10 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_array_append(char **array, char *add)
{
	char	**new;
	size_t	size;

	size = 0;
	while (array && array[size])
		++size;
	new = (char **)malloc(sizeof(char *) * (size + 1 + 1));
	if (new == NULL)
		return (NULL);
	new[size] = add;
	new[size + 1] = NULL;
	while (size--)
		new[size] = array[size];
	free(array);
	return (new);
}
