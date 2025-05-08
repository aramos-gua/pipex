/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:01:10 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 13:01:11 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_in_str(char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*trimmed;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && c_in_str(*start, set))
		start++;
	end = s1 + ft_strlen(s1);
	while (end > start && c_in_str(*(end -1), set))
		end--;
	len = end - start;
	trimmed = ft_substr(start, 0, len);
	if (!trimmed)
		return (NULL);
	trimmed[len] = '\0';
	return (trimmed);
}

//int	main(void)
//{
//	char const	s1[] = "aaaeiouuohella@ouioa";
//	char const	set[] = "aeiou";
//
//	printf("%s", ft_strtrim(s1, set));
//	return (0);
//}
