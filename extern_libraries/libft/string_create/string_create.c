/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_create.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:32 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:46:44 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
char	*ft_substr(t_cchr *s, uint32_t start, size_t len);

/*
	Used functions:
	- malloc
	- ft_strlen
*/
char	*ft_substr(t_cchr *s, uint32_t start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		len = 0;
	else if ((s_len - start) < len)
		len = s_len - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		++i;
	}
	ptr[i] = '\0';
	return (ptr);
}