/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:46:27 by joni          #+#    #+#                 */
/*   Updated: 2025/01/18 21:58:21 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_fd(const char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) < 0)
		return ;
}
