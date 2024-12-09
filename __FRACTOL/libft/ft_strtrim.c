/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdobos <jdobos@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 17:55:23 by jdobos        #+#    #+#                 */
/*   Updated: 2024/04/25 16:47:59 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const ch, char const *set)
{
	while (set)
	{
		if (ch == *set)
			return (1);
		if (*set == '\0')
			return (0);
		set++;
	}
	return (0);
}

// changed "j - i < 0 to j - i == 0" while working on fractol
static int	count(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (check(s1[i], set) == 1 && s1[i])
		i++;
	while (check(s1[j], set) == 1 && j >= i)
	{
		j--;
		if (j - i == 0)
			return (j - i);
	}
	return (j - i);
}

static void	writer(char const *s1, char const *set, char *r, size_t l)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (check(s1[i], set) == 1)
		i++;
	while (s1[i] && j < l + 1)
	{
		r[j] = s1[i];
		i++;
		j++;
	}
	r[j] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*r;
	int		l;

	l = count(s1, set);
	if (l < 0)
	{
		r = (char *) malloc(1 * sizeof(char));
		if (!r)
			return (NULL);
		*r = '\0';
		return (r);
	}
	r = (char *) malloc((l + 2) * sizeof(char));
	if (!r)
		return (NULL);
	writer(s1, set, r, l);
	return (r);
}

// int	main(void)
// {
// 	char *r;
// 	printf("%s\n", ft_strtrim("abcdba", "abc"));
// 	r = ft_strtrim("abcdba", "abc");
// 	free(r);
// 	return (0);
// }
