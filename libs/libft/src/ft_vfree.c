/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vfree.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 15:03:36 by joni          #+#    #+#                 */
/*   Updated: 2024/12/14 13:07:55 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Frees void* if != NULL, and sets it to NULL.
void	ft_vfree(void **ptr)
{
	if (ptr && *ptr)
		free(*ptr);
	*ptr = NULL;
}
