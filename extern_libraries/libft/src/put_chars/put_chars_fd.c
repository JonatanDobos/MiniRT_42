/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_chars_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:50 by rjw           #+#    #+#                 */
/*   Updated: 2025/01/17 18:54:06 by jdobos        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// perror
#include <libft.h>

/*
	Used functions:
	- write
*/
void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		perror("ft_putchar_fd: write");
}

/*
	Used functions:
	- write
*/
void	ft_putendl_fd(t_cchr *s, int fd)
{
	char	destination[BUFFER_SIZE];
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		destination[i] = *s;
		++s;
		if (i == (BUFFER_SIZE - 1))
		{
			if (write(fd, destination, BUFFER_SIZE) == -1)
			{
				perror("ft_putendl_fd: write");
				return ;
			}
			i = 0;
			continue ;
		}
		++i;
	}
	destination[i] = '\n';
	if (write(fd, destination, i + 1) == -1)
		perror("ft_putendl_fd: write");
}

/*
	Used functions:
	- write
*/
void	ft_putnbr_fd(int n, int fd)
{
	char		store[12];
	char		*number;
	uint32_t	negative;

	store[11] = '\0';
	number = &store[11];
	if (n == 0)
	{
		if (write(fd, "0", 1) == -1)
			perror("ft_putnbr_fd: write");
		return ;
	}
	negative = n;
	if (n < 0)
		negative = -n;
	while (negative != 0)
	{
		*(--number) = '0' + (negative % 10);
		negative /= 10;
	}
	if (n < 0)
		*(--number) = '-';
	if (write(fd, number, &store[11] - number) == -1)
		perror("ft_putnbr_fd: write");
}

/*
	Used functions:
	- write
*/
void	ft_putstr_fd(t_cchr *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		perror("ft_putstr_fd: write");
}
