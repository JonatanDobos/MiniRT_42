/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_count.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:31 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:42:32 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
int	spec_count_one(t_p *c, t_fl *f);
int	spec_count_two(t_p *c, t_fl *f);
int	signed_count(int n);
int	unsigned_count(t_fl *f, t_ul n);
int	ft_ultoa_base(t_fl *f, t_ul n, char *str);

int	spec_count_one(t_p *c, t_fl *f)
{
	char	*null_check;

	if (f->sp == 'c')
	{
		va_arg(c->va, int);
		return (1);
	}
	else if (f->sp == 's')
	{
		null_check = va_arg(c->va, char *);
		if (null_check == NULL || null_check == 0)
		{
			return (6);
		}
		else
		{
			return (ft_strlen(null_check));
		}
	}
	return (signed_count(va_arg(c->va, int)));
}

int	spec_count_two(t_p *c, t_fl *f)
{
	int	i;

	i = 0;
	if (f->sp == 'p')
	{
		i = unsigned_count(f, va_arg(c->va, t_ul));
		if (i == 0)
		{
			i = 5;
		}
		else
		{
			i = i + 2;
		}
	}
	else if (c_in_str(f->sp, "uxX") == true)
	{
		return (unsigned_count(f, va_arg(c->va, uint32_t)));
	}
	else if (f->sp == '%')
	{
		return (1);
	}
	return (i);
}

int	signed_count(int n)
{
	int	word_size;

	word_size = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		word_size += 1;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		word_size += 1;
	}
	return (word_size);
}

int	unsigned_count(t_fl *f, t_ul n)
{
	int	word_size;

	if (n == 0)
	{
		if (f->sp == 'p')
		{
			return (0);
		}
		else
		{
			return (1);
		}
	}
	word_size = 0;
	while (n != 0)
	{
		n /= f->b_num;
		word_size = word_size + 1;
	}
	return (word_size);
}

int	ft_ultoa_base(t_fl *f, t_ul n, char *str)
{
	char	store[18];
	short	i;

	move_num_chr(store, '\0', 18);
	if (n == 0)
	{
		str[0] = '0';
		return (1);
	}
	i = 16;
	while (n != 0)
	{
		store[i] = f->base[n % f->b_num];
		n /= f->b_num;
		--i;
	}
	return (move_str(str, &store[i + 1]));
}
