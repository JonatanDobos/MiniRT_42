/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:00 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:45:55 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
int	signed_decimal_base(char *str, int n);
int	move_str(char *dst, t_cchr *src);
int	move_num_src(char *dst, t_cchr *src, int num);
int	move_num_chr(char *str, t_cchr c, int n);

int	signed_decimal_base(char *str, int n)
{
	char	*base;
	char	store[12];
	char	*number;
	long	negative;

	base = "0123456789";
	store[11] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (1);
	}
	negative = n;
	if (negative < 0)
		negative *= -1;
	number = &store[11];
	while (negative != 0)
	{
		*(--number) = base[negative % 10];
		negative /= 10;
	}
	if (n < 0)
		*(--number) = '-';
	return (move_str(str, number));
}

int	move_str(char *dst, t_cchr *src)
{
	short	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		++i;
	}
	return (i);
}

int	move_num_src(char *dst, t_cchr *src, int num)
{
	short	i;

	i = 0;
	while (src[i] != '\0' && num > 0)
	{
		dst[i] = src[i];
		++i;
		--num;
	}
	return (i);
}

int	move_num_chr(char *str, t_cchr c, int n)
{
	short	i;

	i = 0;
	while (i < n)
	{
		str[i] = c;
		++i;
	}
	return (i);
}
