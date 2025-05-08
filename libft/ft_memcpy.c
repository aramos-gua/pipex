/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:04 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:58:06 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = dest;
	while (i++ < n)
		*(unsigned char *)dest++ = *(unsigned const char *)src++;
	return (ptr);
}

//int	main(void)
//{
//	char	src[50] = "HelloTrying to understand this now, oh my dog!";
//	char	dest[50] = "bbbbbbbbbb";
//
//	ft_memcpy(dest, src, 5);
//	printf("%s", dest);
//	return (0);
//}
