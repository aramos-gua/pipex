/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:57:05 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:57:07 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;

	if (!lst)
		return (NULL);
	new_node = ft_lstnew(f(lst -> content));
	if (!new_node)
		return (NULL);
	new_list = new_node;
	lst = lst -> next;
	while (lst != NULL)
	{
		new_node -> next = ft_lstnew(f(lst -> content));
		if (!new_node -> next)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node = new_node -> next;
		lst = lst -> next;
	}
	return (new_list);
}
