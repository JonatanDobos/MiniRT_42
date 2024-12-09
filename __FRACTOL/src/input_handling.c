/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:45:05 by jdobos        #+#    #+#                 */
/*   Updated: 2024/06/11 14:11:10 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

int	num_check(t_fractal *f, char *arg, int i)
{
	int	c;

	c = 0;
	if (arg[i] == '-')
		i++;
	if (!(ft_isdigit(arg[i])))
		ft_error(f, ERR_MESSAGE);
	while (arg[i] && (ft_isdigit(arg[i]) || arg[i] == '.'))
	{
		if (arg[i] == '.')
			c++;
		i++;
	}
	if (c > 1)
		ft_error(f, ERR_MESSAGE);
	return (i);
}

bool	arg_check(t_fractal *f, char *arg)
{
	int	i;

	if (!arg || ft_strlen(arg) > 1000 || ft_strlen(arg) < 4)
		ft_error(f, ERR_MESSAGE);
	i = 0;
	i = num_check(f, arg, i);
	if (arg[i] != ',' || arg[i + 1] != ' ' || \
	(!ft_isdigit(arg[i + 2]) && arg[i + 2] != '-'))
		ft_error(f, ERR_MESSAGE);
	i += 2;
	i = num_check(f, arg, i);
	if ((int)ft_strlen(arg) != i)
		ft_error(f, ERR_MESSAGE);
	return (true);
}

static short	min_check(char c, int *i)
{
	if (c == '-')
	{
		*i = 1;
		return (-1);
	}
	else
	{
		*i = 0;
		return (1);
	}
}

static double	ft_atof(char *arg)
{
	double	num;
	int		i;
	int		mult;
	int		c;

	num = 0;
	mult = min_check(arg[0], &i);
	while (arg[i] && ft_isdigit(arg[i]))
	{
		num = num * 10 + (arg[i] - '0');
		i++;
	}
	c = i;
	if (arg[i] != '.')
		return (num * mult);
	i++;
	while (arg[i] && ft_isdigit(arg[i]))
	{
		num += (double)(arg[i] - '0') / pow(10, (double)(i - c));
		i++;
	}
	return (num * mult);
}

void	assign_jul_c(t_fractal *f, char *arg)
{
	f->julia_x = ft_atof(arg);
	while (*arg != ' ')
		arg++;
	f->julia_y = ft_atof(++arg);
}
