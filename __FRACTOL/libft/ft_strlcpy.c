/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:27 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:40:40 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// int	main(void)
// {
// 	char	dest[] = "AAAAAAAAAA";
// 	char	src[] = "coucou";
// 	printf("Libft: %zu\n", ft_strlcpy(dest, src, 2));
// 	printf("dest: %s\n", dest);
// 	printf("src: %s\n", src);
// 	return 0;
// }