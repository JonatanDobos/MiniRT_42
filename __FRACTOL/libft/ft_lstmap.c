/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdobos <jdobos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:54:46 by joni              #+#    #+#             */
/*   Updated: 2023/10/30 18:01:12 by jdobos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*temp_cont;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	while (lst != NULL)
	{
		temp_cont = f(lst->content);
		new = ft_lstnew(temp_cont);
		if (new == NULL)
		{
			del(temp_cont);
			ft_lstclear(&head, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&head, new);
	}
	return (head);
}
