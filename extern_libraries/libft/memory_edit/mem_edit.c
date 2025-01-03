/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_edit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:32:47 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:32:55 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

/*
	Used functions:
	- ft_memset
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*tmp++ = *(t_uchar *)src++;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp;

	tmp = dest;
	if (src > dest)
		while (n--)
			*(char *)tmp++ = *(char *)src++;
	if (dest > src)
		while (n--)
			*((char *)dest + n) = *((char *)src + n);
	return (dest);
}

void	*ft_memset(void *b, int c, size_t len)
{
	t_uchar	*charb;

	charb = b;
	while (len--)
		*charb++ = (t_uchar)c;
	return (b);
}
