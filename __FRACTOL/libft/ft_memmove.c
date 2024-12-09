/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:12 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/23 18:52:18 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, void *s, size_t size)
{
	unsigned char	*des;
	unsigned char	*src;
	size_t			i;

	des = (unsigned char *)d;
	src = (unsigned char *)s;
	i = 0;
	if (!(d || s))
		return (NULL);
	if (d < s)
	{
		while (size--)
		{
			des[i] = src[i];
			i++;
		}
	}
	if (d > s)
	{
		while (size--)
			des[size] = src[size];
	}
	return (d);
}

// int	main(void)
// {
// 	char s1[] = "Hallo";
// 	char s2[] = "Bye";
// 	printf("\nbefore: s1: %s\ns2: %s,\n\n", s1, s2);
// 	memmove((s1+2), s1, 10);
// 	printf("sys: s1: %s\ns2: %s,\n\n", s1, s2);
// 	char st1[] = "Hallo";
// 	char st2[] = "Bye";
// 	ft_memmove((st1+2), st1, 10);
// 	printf("mine: s1: %s\ns2: %s,\n\n", st1, st2);
// }