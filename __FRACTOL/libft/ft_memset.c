/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:14 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:40:02 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t l)
{
	void	*t;

	t = b;
	while (l--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (t);
}

// int	main(void)
// {
// 	char s1[] = "Hello";
// 	char s2 = '1';
// 	printf("b sys: %s\n", s1);
// 	memset(s1, 50, 3);
// 	printf("a sys: %s\n", s1);
// 	char st1[] = "Hello";
// 	char st2 = '1';
// 	ft_memset(st1, 50, 3);
// 	printf("a mine: %s\n", st1);
// }