/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_null_and_terminator_check.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:29:59 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:30:01 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Global Functions
bool	str0_ok(t_cchr *s1);
bool	strs0_ok(t_cchr *s1, t_cchr *s2);
bool	dpstr0_ok(char **s1);
bool	dpstrs0_ok(char **s1, char **s2);

bool	str0_ok(t_cchr *s1)
{
	return (!(s1 == NULL || *s1 == '\0'));
}

bool	strs0_ok(t_cchr *s1, t_cchr *s2)
{
	return (str0_ok(s1) == true && str0_ok(s2) == true);
}

//	dp = double pointer
bool	dpstr0_ok(char **s1)
{
	return (!(s1 == NULL || *s1 == NULL || **s1 == '\0'));
}

//	dp = double pointer
bool	dpstrs0_ok(char **s1, char **s2)
{
	return (dpstr0_ok(s1) == true && dpstr0_ok(s2) == true);
}
