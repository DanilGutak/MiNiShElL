/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:51:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/30 16:25:45 by dgutak           ###   ########.fr       */
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

int	print_error(t_data *data, char *str, int exit_code)
{
	if (exit_code == 1)
	{
		ft_printf_fd(2, "minishell: %s:", str);
		perror(" ");
	}
	data->exit_code = exit_code;
	return (1);
}
