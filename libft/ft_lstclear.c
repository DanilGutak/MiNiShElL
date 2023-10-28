/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:50:37 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 18:29:24 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(char *, char *))
{
	t_list	*point;
	t_list	*temp;

	point = *lst;
	while (point != NULL)
	{
		temp = point->next;
		del(point->key, point->value);
		free(point);
		point = temp;
	}
	*lst = NULL;
}
