/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:56 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/18 19:35:34 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
int		ft_printf_fd(int fd, t_cchr *format, ...);
int		ft_printf(t_cchr *format, ...);
int		ft_format(t_p *c);
void	spec_str_one(t_p *p, t_fl *f);
void	spec_str_two(t_p *p, t_fl *f);

int	ft_printf_fd(int fd, t_cchr *format, ...)
{
	t_p	count;
	t_p	print;
	int	total;

	if (format == 0)
		return (-1);
	count.fmt = format;
	count.count_or_str = true;
	va_start(count.va, format);
	total = ft_format(&count);
	va_end(count.va);
	print.str = (char *)malloc((total + 1) * sizeof(char));
	if (print.str == NULL)
		return (0);
	print.str[total] = '\0';
	print.fmt = format;
	print.count_or_str = false;
	va_start(print.va, format);
	ft_format(&print);
	if (write(fd, print.str, total) == -1)
		perror("ft_printf_fd: write:");
	va_end(print.va);
	free(print.str);
	return (total);
}

int	ft_printf(t_cchr *format, ...)
{
	t_p	count;
	t_p	print;
	int	total;

	if (format == 0)
		return (-1);
	count.fmt = format;
	count.count_or_str = true;
	va_start(count.va, format);
	total = ft_format(&count);
	va_end(count.va);
	print.str = (char *)malloc((total + 1) * sizeof(char));
	if (print.str == NULL)
		return (0);
	print.str[total] = '\0';
	print.fmt = format;
	print.count_or_str = false;
	va_start(print.va, format);
	ft_format(&print);
	if (write(STDOUT, print.str, total) == -1)
		perror("ft_printf_fd: write:");
	va_end(print.va);
	free(print.str);
	return (total);
}

int	ft_format(t_p *c)
{
	t_fl	flags;

	c->i = 0;
	c->mal = 0;
	c->k = 0;
	while (c->fmt && c->fmt[c->k] != '\0')
	{
		c->spec = parse_format(c, &flags, c->k);
		if (c->spec == -1)
		{
			if (c->count_or_str == true)
				++c->mal;
			else
				c->i += move_num_chr(&c->str[c->i], c->fmt[c->k], 1);
			++c->k;
			continue ;
		}
		else
		{
			flag_check(c, &flags);
		}
		++c->k;
	}
	return (c->mal);
}

void	spec_str_one(t_p *p, t_fl *f)
{
	char	*null_check;

	if (f->sp == 'c')
	{
		p->i += move_num_chr(p->str + p->i, va_arg(p->va, int), 1);
	}
	else if (f->sp == 's')
	{
		null_check = va_arg(p->va, char *);
		if (null_check == NULL || null_check == 0)
		{
			p->i += move_str(p->str + p->i, "(null)");
		}
		else
		{
			p->i += move_str(p->str + p->i, null_check);
		}
	}
	else if (f->sp == 'd' || f->sp == 'i')
	{
		p->i += signed_decimal_base(p->str + p->i, va_arg(p->va, int));
	}
}

void	spec_str_two(t_p *p, t_fl *f)
{
	if (f->sp == 'p')
	{
		f->nbr = va_arg(p->va, t_ul);
		if (f->nbr == 0)
		{
			p->i += move_str(p->str + p->i, "(nil)");
		}
		else
		{
			p->i += move_str(p->str + p->i, "0x");
			p->i += ft_ultoa_base(f, f->nbr, p->str + p->i);
		}
	}
	else if (f->sp == 'x' || f->sp == 'X' || f->sp == 'u')
	{
		p->i += ft_ultoa_base(f, va_arg(p->va, uint32_t), p->str + p->i);
	}
	else if (f->sp == '%')
	{
		p->i += move_str(p->str + p->i, "%");
	}
}
