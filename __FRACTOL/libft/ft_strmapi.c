/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:17:05 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:40:46 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_touppermod(unsigned int i, char *c)
// {
// 	if (*c >= 97 && *c <= 122)
// 		*c = *c - 32;
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*arr;
	size_t	i;

	i = 0;
	arr = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

// int	main(void)
// {
// 	char *out;
// 	char s[] = "Heeee6eellloIo";
// 	out = ft_strmapi(s, ft_touppermod);
// 	printf("%s\n", out);
// 	return (0);
// }