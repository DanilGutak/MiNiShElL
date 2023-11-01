/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:36:22 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/01 19:53:58 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_strcat(const char *s1, const char *s2)
{
	char	*res;
	char	*buffer;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (ft_strdup((char *) s1));
	if (!s1)
		return (ft_strdup((char *) s2));
	res = (char *)malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	buffer = res;
	while (s1 && *s1)
		*res++ = *s1++;
	while (s2 && *s2)
		*res++ = *s2++;
	*res = '\0';
	return (buffer);
}

