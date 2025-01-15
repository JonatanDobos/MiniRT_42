/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deallocation.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:41:01 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/09 21:00:30 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
	Used functions:
	- free
	
	usage:
	char *ptr = "see this as a malloced pointer";

	free_ptr(&ptr);
*/
void	*free_ptr(void **ptr)
{
	if (dp_ptr_ok(ptr) == true)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

/*
	Used functions:
	- free

	usage:
	char *str = "see this as a malloced string";

	free_str((char **)&str);
*/
void	*free_str(char **str)
{
	if (dpstr_ok(str) == true)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
