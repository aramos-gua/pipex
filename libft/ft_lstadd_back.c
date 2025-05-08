/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:56:18 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:56:20 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = new;
}
//
//int	main(void)
//{
//	t_list	*node;
//	t_list	*sec_node;
//	t_list	*tr_node;
//	t_list	*qua_node;
//
//	node = ft_lstnew("a");
//	printf("Creation of first node: %s\n", (char *)node -> content);
//	printf("Address of FIRST node: %p\n", node);
//	printf("Address of next: %p\n", node -> next);
//	sec_node = ft_lstnew("b");
//	ft_lstadd_back(&node, sec_node);
//	printf("Creation of second node: %s\n", (char *)sec_node -> content);
//	printf("Address of SECOND node: %p\n", sec_node);
//	printf("Address of next: %p\n", sec_node -> next);
//	tr_node = ft_lstnew("c");
//	ft_lstadd_back(&node, tr_node);
//	printf("Creation of third node: %s\n", (char *)tr_node -> content);
//	printf("Address of THIRD node: %p\n", tr_node);
//	printf("Address of next: %p\n", tr_node -> next);
//	qua_node = ft_lstnew("d");
//	ft_lstadd_back(&node, qua_node);
//	printf("Creation of forth node: %s\n", (char *)qua_node -> content);
//	printf("Address of FOURTH node: %p\n", qua_node);
//	printf("Address of next: %p\n", qua_node -> next);
//	printf("%d\n\n", ft_lstsize(node));
//
//	while(node != NULL){
//		printf("content: %s, address: %p -> ", (char *)node-> content, node);
//		node = node -> next;
//	}
//	return (0);
//}
