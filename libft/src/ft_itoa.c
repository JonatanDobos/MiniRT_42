/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:39:55 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:40:39 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putnbr_ptr(char *ptr, int n)
{
	size_t	len;

	len = ft_intlen(n);
	if (n == INT_MIN)
	{
		ft_strlcpy(ptr, "-2147483648", 13);
		return ;
	}
	if (n < 0)
	{
		*ptr = '-';
		n = -n;
	}
	else
		*ptr = '0';
	ptr[len] = '\0';
	while (n != 0)
	{
		ptr[--len] = (n % 10) + 48;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	nlen;

	nlen = ft_intlen(n);
	ptr = (char *)malloc((nlen + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_putnbr_ptr(ptr, n);
	return (ptr);
}
