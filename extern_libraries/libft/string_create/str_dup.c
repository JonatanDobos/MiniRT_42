/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_dup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:31:39 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:46:41 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
char	*ft_strdup(t_cchr *s);
char	*strdup_safe(t_cchr *s);
char	*strdup_len(t_cchr *s, size_t size);
char	*strdup_len_free(char **s, size_t size);

/*
	Used functions:
	- malloc
	- ft_strlen
	- ft_strlcpy
*/
char	*ft_strdup(t_cchr *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

/*
	Used functions:
	- malloc
	- ft_strlen
	- ft_strlcpy
*/
char	*strdup_safe(t_cchr *s)
{
	char	*str;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

/*
	Used functions:
	- malloc
	- ft_strlen
	- ft_strlcpy
*/
char	*strdup_len(t_cchr *s, size_t size)
{
	char	*str;
	size_t	len;

	if (s == NULL || size == 0)
		return (NULL);
	len = ft_strlen(s);
	if (size < len)
		len = size;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

/*
	Usage, if 's' is NULL or malloc fails free 's'

	Used functions:
	- malloc
	- ft_strlen
	- ft_strlcpy
*/
char	*strdup_len_free(char **s, size_t size)
{
	char	*str;
	size_t	len;

	if (dpstr_ok(s) == false || size == 0)
		return (free_str(s));
	len = ft_strlen(*s);
	if (size < len)
		len = size;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (free_str(s));
	ft_strlcpy(str, *s, len + 1);
	free_str(s);
	return (str);
}

/*
	Usage, if 's' is NULL or malloc fails don't free 's'

	Used functions:
	- malloc
	- ft_strlen
	- ft_strlcpy
	- free_str
*/
char	*strdup_size_free(char **s, size_t size)
{
	char	*str;
	size_t	len;

	if (dpstr_ok(s) == false || size == 0)
		return (NULL);
	len = ft_strlen(*s);
	if (size < len)
		len = size;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, *s, len + 1);
	free_str(s);
	return (str);
}