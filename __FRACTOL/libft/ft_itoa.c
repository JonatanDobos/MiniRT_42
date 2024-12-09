/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:10:56 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:39:04 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter(int n)
{
	size_t	i;

	i = 2;
	if (n == -2147483648)
		return (12);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	mystrrev(char *str)
{
	char	temp;
	int		b;
	int		e;

	b = 0;
	e = ft_strlen(str) - 1;
	if (str[b] == '-')
		b++;
	while (b < e)
	{
		temp = str[b];
		str[b] = str[e];
		str[e] = temp;
		b++;
		e--;
	}
	return ;
}

static int	min(char *asc, size_t *i)
{
	int	r;

	r = 214748364;
	asc[*i] = '-';
	*i += 1;
	asc[*i] = '8';
	*i += 1;
	return (r);
}

char	*ft_itoa(int n)
{
	char	*ascii;
	size_t	i;

	i = 0;
	ascii = (char *) malloc(counter(n) * sizeof(char));
	if (!(ascii))
		return (NULL);
	if (n == -2147483648)
		n = min(ascii, &i);
	if (n < 0)
	{
		ascii[i++] = '-';
		n = n * -1;
	}
	while (n > 9)
	{
		ascii[i++] = n % 10 + 48;
		n = n / 10;
	}
	ascii[i++] = n + 48;
	ascii[i] = '\0';
	mystrrev(ascii);
	return (ascii);
}

// int	main(void)
// {
// 	int i = 4242;
// 	printf("out: %s\n", ft_itoa(i));
// 	return (0);
// }