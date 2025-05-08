/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:57:29 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:57:32 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst -> next;
	}
	return (size);
}

//int	main(void)
//{
//	t_list	*node;
//	t_list	*sec_node;
//	t_list	*tr_node;
//	t_list	*qua_node;
//
//	node = ft_lstnew("423");
//	printf("Creation of first node: %s\n", (char *)node -> content);
//	printf("Address of FIRST node: %p\n", node);
//	printf("Address of next: %p\n", node -> next);
//	sec_node = ft_lstnew("123");
//	ft_lstadd_front(&node, sec_node);
//	printf("Creation of second node: %s\n", (char *)sec_node -> content);
//	printf("Address of SECOND node: %p\n", sec_node);
//	printf("Address of next: %p\n", sec_node -> next);
//	tr_node = ft_lstnew("123");
//	ft_lstadd_front(&node, tr_node);
//	printf("Creation of third node: %s\n", (char *)tr_node -> content);
//	printf("Address of THIRD node: %p\n", tr_node);
//	printf("Address of next: %p\n", tr_node -> next);
//	qua_node = ft_lstnew("123");
//	ft_lstadd_front(&node, qua_node);
//	printf("Creation of forth node: %s\n", (char *)qua_node -> content);
//	printf("Address of FOURTH node: %p\n", qua_node);
//	printf("Address of next: %p\n", qua_node -> next);
//	printf("%d\n\n", ft_lstsize(node));
//
//	while(node != NULL){
//		printf("%p->", node);
//		node = node -> next;
//	}
//	return (0);
//}
