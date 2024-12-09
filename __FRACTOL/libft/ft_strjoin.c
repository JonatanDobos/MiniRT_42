/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:48:57 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:40:33 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1) + ft_strlen(s2) + 1;
	r = (char *) malloc(j * sizeof(char));
	if (!(r))
		return (NULL);
	j = ft_strlen(s1);
	while (i < j)
	{
		r[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
		r[j++] = s2[i++];
	r[j] = '\0';
	return (r);
}

// int	main(void)
// {
// 	char *out;
// 	char s[] = "Mother ";
// 	char s2[] = "trucker";
// 	out = ft_strjoin(s, s2);
// 	printf("%s\n", out);
// 	return (0);
// }