/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:10 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:39:56 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!(dest || src))
		return (NULL);
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}

// int	main(void)
// {
// 	char s1[5];
// 	char s2[] = "Hello";
// 	int i1[2];
// 	int i2[] = {1,2};
// 	memcpy(s1, s2, 3);
// 	memcpy(i1, i2, 0);
// 	printf("sys: %d\n", i1[1]);
// 	printf("sys: %s\n", s1);

// 	char s3[5];
// 	char s4[] = "Hello";
// 	int i3[2];
// 	int i4[] = {1,2};
// 	ft_memcpy(s3, s4, 3);
// 	ft_memcpy(i3, i4, 0);
// 	printf("mine: %d\n", i3[1]);
// 	printf("mine: %s\n", s3);
// 	return 0;
// }