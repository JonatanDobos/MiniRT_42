/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deallocation.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:41:01 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:41:04 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
void	*free_ptr(void **ptr);
void	*free_str(char **str);

/*
	Used functions:
	- free
	
	usage:
	char *ptr = "see this as a malloced pointer";

	free_ptr((char **)&ptr);
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
