/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:19:59 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 20:43:18 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(int fd, va_list args, const char format)
{
	unsigned long	ptr;

	if (format == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	if (format == '%')
		return (ft_putchar_fd('%', fd));
	if (format == 's')
		return (ft_putstr_fd(va_arg(args, char *), fd));
	if (format == 'd' || format == 'i')
		return (ft_putnbr_fd(va_arg(args, int), fd));
	if (format == 'u')
		return (ft_putnbru_fd(va_arg(args, int), fd));
	else if (format == 'x' || format == 'X')
		return (ft_printhex_fd(va_arg(args, unsigned int), format, fd));
	if (format == 'p')
	{
		ptr = va_arg(args, unsigned long);
		if (!ptr)
			return (ft_putstr_fd("(nil)", fd));
		return (ft_printhex_fd(ptr, format, fd));
	}
	return (0);
}

int	ft_printf_fd(int fd, const char *format, ...)
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
			ret += ft_check(fd, args, format[i + 1]);
			i++;
		}
		else
			ret += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (ret);
}
