/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:08:07 by dgutak            #+#    #+#             */
/*   Updated: 2023/06/11 15:28:02 by dgutak           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*temp;

	ret = NULL;
	if (!f || !del)
		return (NULL);
	while (lst != NULL)
	{
		temp = malloc(sizeof(t_list));
		if (!temp)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		temp->content = f(lst->content);
		ft_lstadd_back(&ret, temp);
		temp->next = 0;
		lst = lst->next;
	}
	return (ret);
}
