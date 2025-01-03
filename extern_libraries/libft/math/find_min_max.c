/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_min_max.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:15 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:33:25 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
size_t	find_min(size_t	n1, size_t n2);
size_t	find_max(size_t	n1, size_t n2);

size_t	find_min(size_t	n1, size_t n2)
{
	if (n1 <= n2)
		return (n1);
	return (n2);
}

size_t	find_max(size_t	n1, size_t n2)
{
	if (n1 >= n2)
		return (n1);
	return (n2);
}
