/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:32 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/23 19:28:46 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t n)
{
	size_t		nl;
	size_t		i;

	if (!(*needle))
		return ((char *)hay);
	nl = ft_strlen(needle);
	while (*hay && n-- >= nl)
	{
		i = 0;
		while (needle[i] && hay[i] == needle[i])
			i++;
		if (needle[i] == '\0')
			return ((char *)hay);
		hay++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char haystack[30] = "aaabcabcd";
// 	char needle[10] = "aabc";
// 	char * empty = (char*)"";
// 	printf("\n%d\n", ft_strnstr(haystack, "abcd", 9) == haystack + 5);
// 	printf("\n%s\n", ft_strnstr(empty, "", 0));
// 	return (0);
// }