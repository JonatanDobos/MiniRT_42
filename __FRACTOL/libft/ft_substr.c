/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:32:47 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:41:04 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count(char const *s, unsigned int start, size_t l)
{
	size_t	i;

	i = 0;
	while (s[start] && l--)
	{
		start++;
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;
	size_t	l;

	if (start >= ft_strlen(s))
	{
		r = (char *) malloc(1 * sizeof(char));
		if (!(r))
			return (NULL);
		*r = '\0';
		return (r);
	}
	l = count(s, start, len);
	r = (char *) malloc((l + 1) * sizeof(char));
	if (!(r))
		return (NULL);
	i = 0;
	while (len-- && s[start])
	{
		r[i] = s[start];
		i++;
		start++;
	}
	r[i] = '\0';
	return (r);
}

// int	main(void)
// {
// 	char s[] = "hello there";
// 	printf("%s\n", ft_substr(s, 9, 3));
// 	return (0);
// }