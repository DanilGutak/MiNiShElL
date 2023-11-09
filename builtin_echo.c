/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:23:27 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/06 20:36:09 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function checks if a given string starts with a hyphen and consists only of the letter 'n'.
 * 
 * @param arg A pointer to a character array (string) representing a command line argument.
 * 
 * @return The function is_flag is returning an integer value. If the argument is NULL, or if the
 * argument is an empty string, or if the first character of the argument is not '-', then the function
 * returns 1. Otherwise, the function checks if all the characters after the '-' are 'n'. If any
 * character is not 'n', the function returns 1. If all the characters after the '-'
 */
int	is_flag(char *arg)
{
	if (!arg || !*arg || *arg != '-')
		return (1);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (1);
		arg++;
	}
	return (0);
}

/*
	Builtin echo
	works with flag -n as well
*/
/**
 * The `builtin_echo` function prints the arguments passed to it, with an optional newline character at
 * the end.
 * 
 * @param data A pointer to a structure that contains data related to the shell program.
 * @param cmd_table The `cmd_table` parameter is a structure that contains information about the
 * command being executed. It includes the command name, arguments, and flags.
 */
void	builtin_echo(t_data *data, t_cmd_table *cmd_table)
{
	int	new_line;
	int	i;

	new_line = is_flag(cmd_table->args[1]);
	i = 1;
	while (is_flag(cmd_table->args[i]) == 0)
		i++;
	while (i < cmd_table->num_args)
	{
		ft_putstr_fd(cmd_table->args[i], STDOUT_FILENO);
		if (i != cmd_table->num_args - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	data->exit_code = 0;
}
