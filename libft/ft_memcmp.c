/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:57:50 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:57:57 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*(const unsigned char *)s1 != *(const unsigned char *)s2)
			return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

//int	main(void)
//{
//	const char	s1[] = {-127, 1, 123, 2};
//	const char	s2[] = {-127, 1, 123, 2};
//
//	printf("%d\n", ft_memcmp(s1, s2, 2));
//	printf("%d", memcmp(s1, s2, 2));
//	return (0);
//}
