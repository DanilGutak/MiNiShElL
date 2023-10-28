/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_blank.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:41:09 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/08 18:49:04 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_blank(const char *str)
{
	const char	arr[] = " \v\f\r\n\t";

	if (!str)
		return (1);
	while (ft_contains(arr, *str))
		str++;
	return (!*str);
}
