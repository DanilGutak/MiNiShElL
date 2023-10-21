/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:15:03 by dgutak            #+#    #+#             */
/*   Updated: 2023/06/08 22:25:18 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dest, char *src, size_t n)
{
	int	len;

	len = ft_strlen(src);
	if (n <= 0)
		return (len);
	while (*src && --n)
		*dest++ = *src++;
	*dest = '\0';
	return (len);
}
