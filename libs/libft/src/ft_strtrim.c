/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:50:25 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:50:27 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		i;
	size_t		s1len;
	char		*trim;
	const char	*s1start;

	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	s1start = s1 + i;
	s1len = ft_strlen(s1start);
	i = 0;
	while (ft_strchr(set, s1start[s1len - 1 - i]) && s1len > i)
		i++;
	trim = (char *)malloc((s1len - i + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, s1start, (s1len - i + 1));
	return (trim);
}
