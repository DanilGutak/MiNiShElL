/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:51:04 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 15:36:38 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* checks for type (0 is for newline) so to print the error accordingly */
/**
 * The function `syntax_error` prints a syntax error message based on the type of error encountered.
 * 
 * @param type The "type" parameter is an integer that represents the type of syntax error encountered.
 * The different values of "type" correspond to different types of unexpected tokens.
 * @param data The parameter `data` is a pointer to a structure of type `t_data`.
 */
void	syntax_error(int type, t_data *data)
{
	data->exit_code = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (type == 1)
		ft_putstr_fd("`|'\n", 2);
	else if (type == 2)
		ft_putstr_fd("`<'\n", 2);
	else if (type == 3)
		ft_putstr_fd("`>'\n", 2);
	else if (type == 4)
		ft_putstr_fd("`>>'\n", 2);
	else if (type == 5)
		ft_putstr_fd("`<<'\n", 2);
	else if (type == 34)
		ft_putstr_fd("`\"'\n", 2);
	else if (type == 39)
		ft_putstr_fd("`''\n", 2);
	else if (type == 0)
		ft_putstr_fd("`newline'\n", 2);
}

/**
 * The function "print_error" prints an error message with a given string and mode, and sets the exit
 * code of the program.
 * 
 * @param data A pointer to a structure of type t_data. This structure likely contains various data
 * related to the program's execution.
 * @param str A string that represents the error message to be printed.
 * @param mode The mode parameter is used to determine the type of error message to be printed. If mode
 * is equal to 1, it means that the error is related to a specific command or operation in the
 * minishell program. In this case, the function will print the error message "minishell:
 * 
 * @return 1.
 */
int	print_error(t_data *data, char *str, int mode)
{
	if (mode == 1)
	{
		ft_printf_fd(2, "minishell: %s: ", str);
		perror("");
		data->exit_code = mode;
	}
	return (1);
}
