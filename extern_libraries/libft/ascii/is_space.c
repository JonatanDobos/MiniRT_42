/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_space.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:24 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:38:28 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
int	ft_isspace(int c);

int	ft_isspace(int c)
{
	return (c_in_str(c, " \t\n\v\f\r"));
}
