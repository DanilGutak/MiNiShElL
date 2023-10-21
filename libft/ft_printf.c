/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:19:59 by dgutak            #+#    #+#             */
/*   Updated: 2023/07/29 14:43:55 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(va_list args, const char format)
{
	unsigned long	ptr;

	if (format == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	if (format == '%')
		return (ft_putchar_fd('%', 1));
	if (format == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	if (format == 'd' || format == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	if (format == 'u')
		return (ft_putnbru_fd(va_arg(args, int), 1));
	else if (format == 'x' || format == 'X')
		return (ft_printhex(va_arg(args, unsigned int), format));
	if (format == 'p')
	{
		ptr = va_arg(args, unsigned long);
		if (!ptr)
			return (ft_putstr_fd("(nil)", 1));
		return (ft_printhex(ptr, format));
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		ret;

	va_start(args, format);
	i = 0;
	ret = 0;
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]) != 0)
		{
			ret += ft_check(args, format[i + 1]);
			i++;
		}
		else
			ret += ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(args);
	return (ret);
}
