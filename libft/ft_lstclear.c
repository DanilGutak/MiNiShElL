/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:50:37 by dgutak            #+#    #+#             */
/*   Updated: 2023/06/11 15:02:15 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*point;
	t_list	*temp;

	point = *lst;
	while (point != NULL)
	{
		temp = point->next;
		del(point->content);
		free(point);
		point = temp;
	}
	*lst = NULL;
}
