/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ptr_null_check.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:31 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:30:32 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
bool	dp_ptr_ok(void **p1);

/*
	true  if exists
	false if NULL
	dp = double pointer
*/
bool	dp_ptr_ok(void **p1)
{
	return (!(p1 == NULL || *p1 == NULL));
}
