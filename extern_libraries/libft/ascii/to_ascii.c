/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   to_ascii.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:38:18 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:38:22 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
inline int	ft_tolower(int c);
inline int	ft_toupper(int c);

inline int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

inline int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
