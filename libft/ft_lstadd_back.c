/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:09:56 by dgutak            #+#    #+#             */
/*   Updated: 2023/06/11 14:16:52 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*point;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	point = *lst;
	while (point->next != NULL)
		point = point->next;
	point->next = new;
}
