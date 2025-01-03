/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_info.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rjw <rjw@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/11 20:33:56 by rjw           #+#    #+#                 */
/*   Updated: 2024/09/11 20:34:01 by rjw           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//	Global Functions
t_lst	*ft_lstlast(t_lst *lst);
int		ft_lstsize(t_lst *lst);

t_lst	*ft_lstlast(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lstsize(t_lst *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		++i;
		lst = lst->next;
	}
	return (i);
}
