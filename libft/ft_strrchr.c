/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:01:02 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 13:01:04 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr = s;

	if (s == NULL || c < 0)
		return (NULL);
	if (c == 0 && s[ft_strlen(s)] == '\0')
		return ((char *)(s + ft_strlen(s)));
	s += ft_strlen(s);
	while (s >= ptr)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}

//int	main(void)
//{
//	const char	s[] = "murcielago gris";
//
//	printf("%s", ft_strrchr(s, (int)'i'));
//	return (0);
//}
