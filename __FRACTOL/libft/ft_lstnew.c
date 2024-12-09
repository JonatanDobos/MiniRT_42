/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:57:07 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/19 16:12:38 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!(new_node))
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int	main(void)
// {
// 	int		*data;
// 	int		print;
// 	t_list	*new_node;

// 	data = malloc(sizeof(int));
// 	if (!(data))
// 		return (0);
// 	*data = 42;
// 	new_node = ft_lstnew(data);

// 	print = *(int *)new_node->content;
// 	printf("%d\n", print);
// 	free(new_node);
// 	free(data);
// 	return (0);
// }
