/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_void_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:35:36 by joni          #+#    #+#                 */
/*   Updated: 2024/12/14 15:01:41 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Frees all pointers in (void*)-array, then array itself.
// Sets *array to NULL.
// Array must be NULL-terminated.
void	ft_free_varray(void ***array)
{
	size_t	i;

	if (array && *array)
	{
		i = 0;
		while (*array[i] != NULL)
			free(*array[i++]);
		free(*array);
		*array = NULL;
	}
}

// Returns: size of (void*)-array.
size_t	ft_varray_size(void **array)
{
	size_t	size;

	size = 0;
	if (!array)
		return (0);
	while (array[size])
		++size;
	return (size);
}

// Returns: (void*)-array with *insert inserted at the given index.
void	**ft_varray_index_ins(void **array, void *insert, size_t index)
{
	size_t	size;
	size_t	i;
	void	**new_array;

	size = 0;
	size = ft_varray_size(array);
	new_array = (void **)malloc(sizeof(void *) * (++size + 1));
	if (!new_array)
		return (NULL);
	new_array[size] = NULL;
	i = size - 1;
	while (size--)
	{
		if (size == index)
			new_array[index] = insert;
		else
			new_array[size] = array[--i];
	}
	free(array);
	return (new_array);
}

// Returns: (void*)-array with *add appended to it.
void	**ft_varray_append(void **array, void *add)
{
	void	**new;
	size_t	size;

	size = 0;
	while (array && array[size])
		++size;
	new = (void **)malloc(sizeof(void *) * (size + 1 + 1));
	if (new == NULL)
		return (NULL);
	new[size] = add;
	new[size + 1] = NULL;
	while (size--)
		new[size] = array[size];
	free(array);
	return (new);
}

// Returns: a duplicate of (void*)-array.
void	**ft_varrdup(void **arr)
{
	void	**dup;
	int		i;

	i = 0;
	while (arr[i])
		++i;
	dup = (void **)malloc((i + 1) * sizeof(void *));
	if (dup == NULL)
		return (NULL);
	dup[i] = NULL;
	while (i--)
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (ft_free_varray(&dup), NULL);
	}
	return (dup);
}
