/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:00:43 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 13:00:44 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*result;
	char	*start_r;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	result = (char *) malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	start_r = result;
	while (s[i] != '\0')
	{
		result[i] = (*f)(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (start_r);
}

//char	my_function(unsigned int index, char c) 
//{
//	(void)index;
//    // For demonstration, convert each character to uppercase
//    if (c >= 'a' && c <= 'z') {
//        return c - ('a' - 'A');
//    }
//    return c;
//}
//
//
//int main()
//{
//    // Input string
//    const char *original_string = "hello world";
//
//    // Call ft_strmapi
//    char *result = ft_strmapi(original_string, my_function);
//
//    // Check if the function call was successful
//    if (result) {
//        printf("Original string: %s\n", original_string);
//        printf("Transformed string: %s\n", result);
//        free(result); // Always free dynamically allocated memory
//    } else {
//        printf("Memory allocation failed.\n");
//    }
//
//    return 0;
//}
