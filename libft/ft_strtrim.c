/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:48:08 by dgutak            #+#    #+#             */
/*   Updated: 2023/09/15 15:11:18 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	if (checkset(*s1, set) == 1)
		s1++;
	j = ft_strlen(s1) - 1;
	if (j >= 0 && checkset(s1[j], set) == 1)
		j--;
	res = malloc(sizeof(char) * (j + 2));
	if (!res)
		return (0);
	while (j-- >= 0)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
