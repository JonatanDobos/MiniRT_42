/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_characters.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:30:24 by rjw           #+#    #+#                 */
/*   Updated: 2025/04/03 15:58:34 by rde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	skip_alpha(const char *str)
{
	const char	*tmp_str = str;

	while (*tmp_str != '\0' && ft_isalpha(*tmp_str) == 1024)
		++tmp_str;
	return (tmp_str - str);
}

size_t	skip_digits(t_cchr *str)
{
	const char	*tmp_str = str;

	while (*tmp_str != '\0' && ft_isdigit(*tmp_str) == true)
		++tmp_str;
	return (tmp_str - str);
}

size_t	skip_signed_digits(const char *str)
{
	bool	is_signed = (*str == '-' || *str == '+');

	return (skip_digits(str + is_signed) + is_signed);
}

size_t	skip_spaces(t_cchr *str)
{
	const char	*tmp_str = str;

	while (ft_isspace(*tmp_str) == true)
		++tmp_str;
	return (tmp_str - str);
}
