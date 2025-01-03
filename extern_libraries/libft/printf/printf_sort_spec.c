/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf_sort_spec.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:18 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:45:19 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
int			flag_check(t_p *c, t_fl *f);

//	Static Functions
static void	bonus_function(t_p *c, t_fl *f);
static void	bonus_flags(int i, t_p *c, t_fl *f);

int	flag_check(t_p *c, t_fl *f)
{
	short	count_flags;

	count_flags = f->f_len + f->width + f->dot;
	if (c->count_or_str == true && count_flags == 0)
	{
		if (c_in_str(f->sp, "csdi") == true)
			c->mal += spec_count_one(c, f);
		else
			c->mal += spec_count_two(c, f);
	}
	else if (c->count_or_str == false && count_flags == 0)
	{
		if (c_in_str(f->sp, "csdi") == true)
			spec_str_one(c, f);
		else
			spec_str_two(c, f);
	}
	else
		bonus_function(c, f);
	return (c->mal);
}

static void	bonus_function(t_p *c, t_fl *f)
{
	short	i;

	if (f->sp == 'c')
	{
		i = 0;
	}
	else if (f->sp == 's')
	{
		i = 1;
	}
	else if (f->sp == 'd' || f->sp == 'i')
	{
		i = 2;
	}
	else
	{
		i = 3;
	}
	if (c->count_or_str == true)
		i += 4;
	bonus_flags(i, c, f);
}

static void	bonus_flags(int i, t_p *c, t_fl *f)
{
	static void	(*count_or_write[8])(t_p *, t_fl *) = {
		chr_bonus_count,
		str_bonus_count,
		int_bonus_count,
		nbr_bonus_count,
		chr_bonus_write,
		str_bonus_write,
		int_bonus_write,
		nbr_bonus_write
	};

	count_or_write[i](c, f);
}
