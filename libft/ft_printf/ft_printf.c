/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:36:19 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 11:36:24 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	bs(const char **str, t_form *format, va_list args)
{
	format -> pad = ' ';
	format -> flags = 0;
	format -> width = -1;
	format -> precision = -1;
	format -> f_specifier = 0;
	parse_flags(str, format);
	parse_width(str, format, args);
	parse_precision(str, format, args);
	parse_specifier(str, format);
	apply_specifier(format, args);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	t_form		format;

	format.p_chars = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			bs(&str, &format, args);
		}
		else
		{
			ft_putchar_fd(*str, 1);
			format.p_chars++;
		}
		str++;
	}
	va_end(args);
	return (format.p_chars);
}
//	current_p_chars = format -> p_chars;
//	*format = (t_form){' ', 0, -1, -1, 0, 0};
//	format -> p_chars = current_p_chars;
