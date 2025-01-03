/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sign.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:02 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:33:13 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
short	sign(int n);
short	sign_d(double n);

short	sign(int n)
{
	if (n >= 0)
		return (n > 0);
	return (-1);
}

/**
 * check on double.
*/
short	sign_d(double n)
{
	if (n >= 0)
		return (n > 0);
	return (-1);
}
