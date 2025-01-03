/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   digit_counter.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:31 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:33:38 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
uint16_t	digit_counter(t_ll n);

uint16_t	digit_counter(t_ll n)
{
	uint16_t	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		++count;
	while (n != 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}
