/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:36:52 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/29 13:37:55 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (0);
	while (split[i])
		i++;
	return (i);
}
