/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_char.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:35 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:42:15 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
void	chr_bonus_count(t_p *c, t_fl *f);
void	chr_bonus_write(t_p *p, t_fl *f);

void	chr_bonus_count(t_p *c, t_fl *f)
{
	va_arg(c->va, int);
	if (f->width == 0)
	{
		++c->mal;
	}
	else
	{
		c->mal += f->width;
	}
}

void	chr_bonus_write(t_p *p, t_fl *f)
{
	if (f->dash == false)
	{
		p->i += move_num_chr(p->str + p->i, ' ', f->width - 1);
	}
	p->str[p->i] = va_arg(p->va, int);
	++p->i;
	if (f->dash == true && f->width > 0)
	{
		p->i += move_num_chr(p->str + p->i, ' ', f->width - 1);
	}
}
