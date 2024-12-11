/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnarr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:49:41 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:49:57 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// find a needle in an array of haystacks
char	*ft_strnarr(char **haystack, char *needle, size_t n)
{
	const size_t	needle_len = ft_strlen(needle);

	while (*haystack && n)
	{
		if (ft_strnstr(*haystack, needle, needle_len))
			return (*haystack);
	}
	return (NULL);
}
