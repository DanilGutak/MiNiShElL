/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:15:03 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 13:42:25 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	res;

	res = ft_strlen(src);
	if (!dst || !src || !size)
		return (res);
	while (*src && --size > 0)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (res);
}
