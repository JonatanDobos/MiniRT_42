/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:50:15 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:50:18 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;

	while (*haystack && n)
	{
		i = 0;
		while (haystack[i] == needle[i] && needle[i] && n - i)
			i++;
		if (needle[i] == '\0')
			return ((char *)haystack);
		haystack++;
		n--;
	}
	if (*needle == '\0')
		return ((char *)haystack);
	return (NULL);
}
