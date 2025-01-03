/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleunin <saleunin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:29:31 by rjw               #+#    #+#             */
/*   Updated: 2024/09/27 11:38:17 by saleunin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
char	*ft_strchr(t_cchr *s, int c);
char	*ft_strnstr(t_cchr *big, t_cchr *little, size_t len);
char	*ft_strrchr(t_cchr *s, int c);

char	*ft_strchr(t_cchr *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		++i;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strnstr(t_cchr *big, t_cchr *little, size_t len)
{
	size_t		i;

	if (len == 0 && *little)
		return (NULL);
	if (!*little)
		return ((char *)big);
	while (*big && len > 0)
	{
		i = 0;
		while (big[i] == little[i] && big[i] && little[i] && len - i)
			++i;
		if (little[i] == '\0')
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}

/*
	Used functions:
	- ft_strlen
*/
char	*ft_strrchr(t_cchr *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		--i;
	}
	if (s[i] == (char)c || (char)c == 0)
		return ((char *)s + i);
	return (NULL);
}
