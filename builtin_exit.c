/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:04:33 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/04 23:12:12 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function atoi_new converts a string representation of a number to a long int, taking into
 * account leading whitespace and sign.
 * 
 * @param str A pointer to a character array that represents a string containing a number.
 * 
 * @return a long int value.
 */
long int	atoi_new(char *str)
{
	long int	x;
	long int	sign;

	x = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\v' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			x = x * 10 + *str - '0';
		else
			break ;
		if ((x > 4294967295 && sign == 1) || (sign == -1 && x > 4294967296))
			return (9876543210);
		str++;
	}
	return (sign * x);
}

/**
 * The function checks if a given string is a valid argument by checking if it starts with a sign or a
 * digit, and if all subsequent characters are digits.
 * 
 * @param str The parameter "str" is a pointer to a character array (string).
 * 
 * @return an integer value. If the argument passed to the function is a valid number (either positive
 * or negative), the function will return 0. If the argument is not a valid number, the function will
 * return 1.
 */
int	check_arg(char *str)
{
	if (*str == '-' || *str == '+' || ft_isdigit(*str) == 1)
		str++;
	else
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		str++;
	}
	return (0);
}

/**
 * The function `builtin_exit_part2` handles the exit command in a shell program, allowing the user to
 * exit the program with a specified exit code.
 * 
 * @param data A pointer to a data structure containing information about the program's state.
 * @param cmd_table A structure containing information about the command being executed, including the
 * arguments passed to it.
 * @param code The parameter "code" is a long integer that represents the exit code for the program.
 * @param count The parameter "count" is an integer that represents the number of arguments passed to
 * the function.
 * 
 * @return Nothing is being returned.
 */
void	builtin_exit_part2(t_data *data, t_cmd_table *cmd_table, long int code,
		int count)
{
	if (count < 2 )
		ft_printf_fd(2, "exit\n");
	if (count < 2 && (!cmd_table || cmd_table->num_args == 1))
	{
		clean_all(data);
		exit(data->exit_code);
	}
	code = atoi_new(cmd_table->args[1]);
	if (code == 9876543210 && ft_printf_fd(2, "minishell: exit: \
		 %s: numeric argument required\n", cmd_table->args[1]))
	{
		data->exit_code = 2;
		if (count != 1)
			return ;
		clean_all(data);
		exit(data->exit_code);
	}
	if (code < 0)
		data->exit_code = 256 + code % 256;
	else
		data->exit_code = code % 256;
	if (count == 1)
		clean_all(data);
	if (count == 1)
		exit(data->exit_code);
}

/**
 * The function `builtin_exit` is used in a shell program to handle the "exit" command, which
 * terminates the program with a specified exit code.
 * 
 * @param data A pointer to a struct that contains data related to the shell program.
 * @param cmd_table A pointer to a structure of type t_cmd_table, which contains information about the
 * command being executed, such as the command name and its arguments.
 * 
 * @return The function is not returning anything.
 */
void	builtin_exit(t_data *data, t_cmd_table *cmd_table)
{
	int	count;

	count = data->cmdt_count;
	if (!cmd_table)
	{
		ft_printf_fd(2, "exit\n");
		clean_all(data);
		exit(data->exit_code);
	}
	if (cmd_table && cmd_table->num_args > 1
		&& check_arg(cmd_table->args[1]) == 1)
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			cmd_table->args[1]);
		data->exit_code = 2;
		if (count < 2)
			clean_all(data);
		if (count < 2)
			exit(data->exit_code);
		return ;
	}
	if (cmd_table && cmd_table->num_args > 2)
		return (ft_printf_fd(2, "minishell: exit: too many arguments\n"),
			(void)(data->exit_code = 1));
	builtin_exit_part2(data, cmd_table, 0, count);
}
