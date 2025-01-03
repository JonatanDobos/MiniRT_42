/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_values.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:50 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:30:51 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
void	swap_str_values(void **s1, void **s2);

void	swap_str_values(void **s1, void **s2)
{
	void	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
