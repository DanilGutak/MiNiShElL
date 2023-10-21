/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:54:28 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/21 16:04:12 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		len;
	int		i;
	char	*temp;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	temp = s1;
	if (!s2 || !s1)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = ft_calloc((len + 1), sizeof(char));
	if (!ret)
		return (free(s1), NULL);
	while (len--)
	{
		if (*temp)
			ret[i++] = *temp++;
		else
			ret[i++] = *s2++;
	}
	free(s1);
	return (ret);
}
