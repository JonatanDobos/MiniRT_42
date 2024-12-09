/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/13 16:44:51 by jdobos        #+#    #+#                 */
/*   Updated: 2024/05/13 16:44:54 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/fractol.h"

t_uint	rgba_to_hex(t_color c)
{
	t_uint	hex;

	hex = ((t_uint)c.r << 24) | ((t_uint)c.g << 16) | \
	((t_uint)c.b << 8) | (t_uint)c.a;
	return (hex);
}

t_color	hex_to_rgba(t_uint hex)
{
	t_color	c;

	c.r = (hex >> 24) & 0xFF;
	c.g = (hex >> 16) & 0xFF;
	c.b = (hex >> 8) & 0xFF;
	c.a = hex & 0xFF;
	return (c);
}

t_uint	round_to_uint(double n)
{
	return ((t_uint)(n + 0.5));
}

t_uint	color_interpolate(t_color c_l, t_color c_h, double t)
{
	t_color	c;

	c.r = round_to_uint((1.0 - t) * c_l.r + t * c_h.r);
	c.g = round_to_uint((1.0 - t) * c_l.g + t * c_h.g);
	c.b = round_to_uint((1.0 - t) * c_l.b + t * c_h.b);
	c.a = round_to_uint((1.0 - t) * c_l.a + t * c_h.a);
	return (rgba_to_hex(c));
}
