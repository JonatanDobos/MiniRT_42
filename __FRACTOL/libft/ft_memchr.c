/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:05 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:39:09 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return ((void *)str);
		str++;
		n--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	str[] = "yo i am john";
// 	char	c = 'i';
// 	int	n = 30;
// 	char	*out = ft_memchr(str, c, n);
// 	if (out != NULL)
// 		printf("out: %d\n", *out);
// 	else	printf("NULL\n");
// 	return (0);
// }