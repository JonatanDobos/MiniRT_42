/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_d.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:49:03 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:49:04 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_d(const char *s1, const char *s2, const char delim)
{
	char			*ptr;
	const size_t	s1len = ft_strlen_null(s1);
	const size_t	s2len = ft_strlen_null(s2);

	ptr = (char *)malloc((s1len + s2len + 2) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, s1len + 1);
	ptr[s1len] = delim;
	ptr[s1len + 1] = '\0';
	ft_strlcat(ptr, s2, s1len + s2len + 2);
	return (ptr);
}
