/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:51:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/22 19:27:45 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	if (msg == '\n')
		ft_putstr_fd("newline", 2);
	else
		ft_putchar_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
}
