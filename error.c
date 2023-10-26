/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:51:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/26 19:37:15 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* checks for type (0 is for newline) so to print the error accordingly */
void	syntax_error(int type)
{
	if (type == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (type == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (type == 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (type == 4)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (type == 5)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (type == 34)
		ft_putstr_fd("minishell: syntax error near unexpected token `\"'\n", 2);
	else if (type == 39)
		ft_putstr_fd("minishell: syntax error near unexpected token `''\n", 2);
	else if (type == 0)
		ft_putstr_fd("minishell: syntax error near \
		unexpected token `newline'\n",
			2);
}
