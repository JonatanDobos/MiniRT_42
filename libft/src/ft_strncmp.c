/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:50:02 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:50:12 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	const unsigned char	*uca = (unsigned char *)a;
	const unsigned char	*ucb = (unsigned char *)b;

	while (n-- && (*uca || *ucb))
		if (*uca++ != *ucb++)
			return (*(uca - 1) - *(ucb - 1));
	return (0);
}
