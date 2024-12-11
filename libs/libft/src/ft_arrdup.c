/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:35:36 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:35:42 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_arrdup(char **arr)
{
	char	**dup;
	int		i;

	i = 0;
	while (arr[i])
		++i;
	dup = (char **)malloc((i + 1) * sizeof(char *));
	if (dup == NULL)
		return (NULL);
	dup[i] = NULL;
	while (i--)
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (ft_free_array(dup), NULL);
	}
	return (dup);
}
