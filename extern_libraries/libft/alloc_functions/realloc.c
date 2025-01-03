/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   realloc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:40:20 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:40:37 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
void	*ft_realloc(void **ptr, size_t new_size, size_t old_size);

/*
	Used functions:
	- free_ptr
	-	free
	- malloc
	- ft_memcpy
	- ft_min
	
	don't return on the same pointer, if malloc fails the old malloced
	pointer will be overwritten with NULL and unable to free the old.
*/
void	*ft_realloc(void **ptr, size_t new_size, size_t old_size)
{
	void	*new;

	if (new_size == 0 && ptr)
		return (free_ptr(ptr));
	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	if (ptr != NULL)
		ft_memcpy(new, *ptr, find_min(new_size, old_size));
	free_ptr(ptr);
	return (new);
}
