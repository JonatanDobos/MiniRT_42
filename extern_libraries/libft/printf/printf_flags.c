/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_flags.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:27 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:43:34 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
int			parse_format(t_p *c, t_fl *f, int k);

//	Static Functions
static void	flags_reset(t_fl *f);
static int	find_spec(t_fl *f, t_cchr fmt, short i);
static int	get_flags(t_p *c, t_fl *f, int k);
static int	get_width_prec(t_p *c, t_fl *f, int k, int *width_prec);

int	parse_format(t_p *c, t_fl *f, int k)
{
	int		begin;
	short	specifier;
	short	i;

	begin = k;
	flags_reset(f);
	if (c->fmt[k] != '%')
		return (-1);
	k++;
	c->k++;
	i = 0;
	specifier = find_spec(f, c->fmt[k], i);
	if (specifier >= 0)
		return (specifier);
	k = get_flags(c, f, k);
	k = get_width_prec(c, f, k, &f->width);
	k = get_width_prec(c, f, k, &f->prec);
	specifier = find_spec(f, c->fmt[k], i);
	if (specifier == -1)
		flags_reset(f);
	c->k += k - begin - 1;
	return (specifier);
}

static void	flags_reset(t_fl *f)
{
	f->space = false;
	f->plus = false;
	f->dash = false;
	f->zero = false;
	f->hash = false;
	f->hsh = 0;
	f->width = 0;
	f->dot = false;
	f->prec = 0;
	f->f_len = 0;
	f->ap_len = 0;
	f->sign = 'X';
	f->stop = false;
	move_num_chr(f->prefix, '\0', 3);
}

static int	find_spec(t_fl *f, t_cchr fmt, short i)
{
	while (SPECIFIER[i] != '\0')
	{
		if (fmt == SPECIFIER[i])
		{
			f->sp = fmt;
			f->b_num = 16;
			f->base = "0123456789abcdef";
			move_str(f->prefix, "0x");
			if (fmt == 'X')
			{
				f->base = "0123456789ABCDEF";
				move_str(f->prefix, "0X");
			}
			else if (c_in_str(fmt, "udi") == true)
			{
				f->base = "0123456789";
				f->b_num = 10;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

static int	get_flags(t_p *c, t_fl *f, int k)
{
	while (c->fmt[k] == ' ' || c->fmt[k] == '+' || c->fmt[k] == '-'
		|| c->fmt[k] == '0' || c->fmt[k] == '#')
	{
		if (c->fmt[k] == ' ')
			f->space = true;
		else if (c->fmt[k] == '+')
			f->plus = true;
		else if (c->fmt[k] == '-')
			f->dash = true;
		else if (c->fmt[k] == '0')
			f->zero = 48;
		else if (c->fmt[k] == '#')
			f->hash = true;
		f->f_len++;
		k++;
	}
	return (k);
}

static int	get_width_prec(t_p *c, t_fl *f, int k, int *width_prec)
{
	if (f->stop == true)
	{
		if (c->fmt[k] != '.')
			return (k);
		f->dot = true;
		++k;
	}
	else
		f->stop = true;
	while (c->fmt[k] >= '0' && c->fmt[k] <= '9')
	{
		*width_prec = *width_prec * 10 + (c->fmt[k] - 48);
		++k;
	}
	return (k);
}
