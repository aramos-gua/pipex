/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:56:26 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:56:27 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}

//int	main(void)
//{
//	t_list	*node;
//	t_list	*sec_node;
//
//	node = ft_lstnew("423");
//	printf("Creation of first node: %s\n", (char *)node -> content);
//	printf("Address of next: %p\n", node -> next);
//	printf("Address of this node: %p\n", node);
//	sec_node = ft_lstnew("123");
//	ft_lstadd_front(&node, sec_node);
//	printf("Creation of second node: %s\n", (char *)sec_node -> content);
//	printf("Address of next: %p\n", sec_node -> next);
//}
