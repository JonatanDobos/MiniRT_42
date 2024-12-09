/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:04:19 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/24 11:40:26 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *) malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!(ptr))
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int	main(void)
// {
// 	char	*out1;
// 	char	*out2;
// 	char	in[] = "String";
// 	out1 = ft_strdup(in);
// 	out2 = strdup(in);
// 	printf("Mine: %s\n", out1);
// 	printf("Mine: %s\n", out2);
// 	free(out1);
// 	free(out2);
// 	return (0);
// }
