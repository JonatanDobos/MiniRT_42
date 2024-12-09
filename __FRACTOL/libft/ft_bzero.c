/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:03:47 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:39:30 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(unsigned char *)s = '\0';
		s++;
		n--;
	}
}

// int	main(void)
// {
// 	char s1[] = "12345";
// 	char s2[] = "12345";
// 	ft_bzero(s1, 4);
// 	bzero(s2, 4);
// 	printf("compare: %d\n", ft_memcmp(s1, s2, 4));
// 	return (0);
// }