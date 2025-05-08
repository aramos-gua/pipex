/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_s_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:37:14 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 11:37:19 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hm_pudding(int len, t_form *format);
static void	pbonus_s_pad(int padding, t_form *format);

//%c speficier
void	pbonus_c(char c, t_form *format)
{
	int		padding;

	padding = format -> width - 1;
	if (!(format -> flags & FLAG_MINUS))
	{
		while (padding-- > 0)
			(format->p_chars) += ft_putchar_fd(' ', 1);
	}
	format->p_chars += ft_putchar_fd(c, 1);
	if (format -> flags & FLAG_MINUS)
	{
		while (padding-- > 0)
			(format->p_chars) += ft_putchar_fd(' ', 1);
	}
}

//%s specifier
void	pbonus_s(const char *str, t_form *format, va_list args)
{
	int	len;
	int	padding;

	len = ft_strlen(str);
	padding = 0;
	if (format -> width > len)
		padding = format -> width - len;
	else if (format -> width == '*' && va_arg(args, int) > len)
		padding = va_arg(args, int) - len;
	if (format -> precision >= 0 && format -> precision < len)
		len = format -> precision;
	if ((format -> width) > (format -> precision) && format -> precision != -1)
		padding = (format -> width) - (format -> precision);
	if (!(format -> flags & FLAG_MINUS))
		pbonus_s_pad(padding, format);
	write(1, str, len);
	format->p_chars += len;
	if (format -> flags & FLAG_MINUS)
		pbonus_s_pad(padding, format);
}

static void	pbonus_s_pad(int padding, t_form *format)
{
	while (padding--)
		(format->p_chars) += ft_putchar_fd(' ', 1);
}

//%u specifier
void	pbonus_u(unsigned int n, t_form *format)
{
	char	*str;
	int		len;

	str = ft_printf_utoa(n);
	if (n == 0 && (format -> precision == 0 || format -> width == 0))
		len = 0;
	else
		len = append_0(&str, format);
	if (!(format -> flags & FLAG_MINUS))
		hm_pudding(len, format);
	if (!(n == 0 && (format -> precision == 0 || format -> width == 0)))
		(format->p_chars) += ft_putstr_fd(str, 1);
	format -> pad = ' ';
	if (format -> flags & FLAG_MINUS)
		hm_pudding(len, format);
	free(str);
}

static void	hm_pudding(int len, t_form *format)
{
	int		padding;

	padding = 0;
	if (format -> width > len)
		padding = format -> width - len;
	if (format -> flags & FLAG_ZERO)
		format -> pad = '0';
	while (padding--)
		(format->p_chars) += ft_putchar_fd(format -> pad, 1);
}
