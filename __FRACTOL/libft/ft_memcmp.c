/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:07 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:39:52 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ls1;
	const unsigned char	*ls2;
	size_t				i;

	ls1 = (const unsigned char *)s1;
	ls2 = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (ls1[i] != ls2[i])
			return (ls1[i] - ls2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char s1[] = "Hello world";
// 	char s2[] = "Hello world";
// 	printf("mine: %d\n", ft_memcmp(s1, s2, 10));
// 	printf("sys: %d\n", memcmp(s1, s2, 10));
// 	return 0;
// }