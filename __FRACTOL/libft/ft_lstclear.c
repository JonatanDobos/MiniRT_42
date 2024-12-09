/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:37:02 by jdobos            #+#    #+#             */
/*   Updated: 2023/10/19 17:49:38 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	if (lst == NULL || del == NULL)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		del(temp->content);
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	*lst = NULL;
}
