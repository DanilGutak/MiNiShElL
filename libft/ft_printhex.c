/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:04:34 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 20:43:10 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex_fd(unsigned long n, char format, int fd)
{
	char	*base;
	int		ret;
	char	buffer[32];
	int		i;

	i = 0;
	ret = 0;
	base = "0123456789abcdef";
	if (format == 'p')
		ret += ft_putstr_fd("0x", fd);
	if (format == 'X')
		base = "0123456789ABCDEF";
	if (n == 0)
		return (ret + ft_putchar_fd('0', fd));
	while (n > 0)
	{
		buffer[i] = base[n % 16];
		n /= 16;
		i++;
	}
	while (i > 0)
		ret += ft_putchar_fd(buffer[--i], fd);
	return (ret);
}
