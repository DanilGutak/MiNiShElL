/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:48:46 by dgutak            #+#    #+#             */
/*   Updated: 2023/06/08 20:21:09 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *to_find, size_t len)
{
	int		i;
	int		j;
	size_t	k;

	i = 0;
	j = 0;
	k = ft_strlen(to_find);
	if (!to_find[j])
		return (str);
	while (str[i] && len >= k)
	{
		while (str[i + j] == to_find[j] && str[i + j])
			j++;
		if (!to_find[j])
			return (str + i);
		i++;
		j = 0;
		len--;
	}
	return (0);
}

/* #include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char	*result;

	result = ft_strnstr("abc", "a", -1);
	printf("ft_strstr: %s\n", result);
	result = strnstr("abc", "a", -1);
	printf("strstr: %s\n", result);
	return (0);
}
 */