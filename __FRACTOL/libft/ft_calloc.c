/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:03:49 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:39:35 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;
	size_t	t;

	t = nmemb * size;
	if (nmemb != 0 && size != 0 && t / nmemb != size)
		return (NULL);
	r = (void *) malloc(t);
	if (r)
		ft_memset(r, 0, t);
	return (r);
}
