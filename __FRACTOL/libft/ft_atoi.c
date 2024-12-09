/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:03:40 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/23 20:14:33 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	v;
	int	c;

	v = 0;
	c = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			c = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		v = v * 10 + (*str - 48);
		str++;
	}
	return (c * v);
}

// int	main(void)
// {
// 	char s[] = "12345";
// 	printf("libft: %d\n", ft_atoi(s));
// 	printf("original: %d\n", atoi(s));
// 	return (0);
// }
