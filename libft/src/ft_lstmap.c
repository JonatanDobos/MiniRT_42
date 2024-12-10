/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: joni <joni@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/03 14:41:55 by joni          #+#    #+#                 */
/*   Updated: 2024/12/03 14:41:57 by joni          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*newnode;
	void	*tmpcont;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	first = NULL;
	while (lst)
	{
		tmpcont = f(lst->content);
		newnode = ft_lstnew(tmpcont);
		if (newnode == NULL)
		{
			del(tmpcont);
			ft_lstclear(&first, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&first, newnode);
	}
	return (first);
}
