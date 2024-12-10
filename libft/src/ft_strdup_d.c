/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup_d.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:47:37 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:48:31 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// includes delimiter \d\0
char	*ft_strdup_d(const char *str, const char delim)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (str[i] && str[i] != delim)
		i++;
	ptr = malloc((i + 1 + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != delim)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i++] = delim;
	ptr[i] = '\0';
	return (ptr);
}
