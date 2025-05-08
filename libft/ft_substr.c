/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:01:17 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 13:01:18 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	char		*start_ptr;
	char const	*new_s;

	if (s == NULL || start > ft_strlen(s))
	{
		ptr = (char *) malloc(1);
		*ptr = '\0';
		return (ptr);
	}
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	ptr = (char *) malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	new_s = s + start;
	start_ptr = ptr;
	while (len-- > 0 && *new_s != '\0')
		*ptr++ = *new_s++;
	*ptr = '\0';
	return (start_ptr);
}

//int	main(void)
//{
//	char const	s[] = "hellohellohello";
//
//	printf("%s\n", ft_substr(s, 5, 10));
//	printf("%s", ft_substr(s, 5, 11));
//	return (0);
//}
