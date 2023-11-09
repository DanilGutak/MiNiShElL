/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:38:28 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/07 14:24:02 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function checks if a given string is invalid, meaning it does not start with a letter or
 * underscore, contains characters other than alphanumeric and underscore, or does not contain an equal
 * sign.
 * 
 * @param str A pointer to a string that needs to be checked for validity.
 * 
 * @return an integer value.
 */
static int	is_invalid(char *str)
{
	if (str == NULL || !(ft_isalpha(*str) || *str == '_'))
		return (1);
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (1);
		str++;
	}
	return (0);
}

/**
 * The function "handle_valid" takes a line of text and extracts the key-value pair separated by an
 * equals sign, then sets the variable in the data structure with the extracted key and value.
 * 
 * @param data A pointer to a struct called "t_data". This struct likely contains some data that needs
 * to be modified or updated based on the key-value pair in the "line" parameter.
 * @param line A string containing a key-value pair in the format "key=value".
 * 
 * @return The function does not have a return type specified, so it is assumed to be returning void.
 */
static void	handle_valid(t_data *data, char *line)
{
	char	*value;
	char	*key;
	int		i;

	if (!line || !*line || !ft_contains(line, '='))
		return ;
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	key = ft_substr(line, 0, i++);
	if (!key)
		return ;
	while (line[i])
		i++;
	value = ft_substr(line, ft_strlen(key) + 1, i);
	if (!value)
	{
		free(key);
		return ;
	}
	set_variable(data, key, value);
	free(value);
	free(key);
}

/**
 * The function "handle_empty" prints the environment variables in a specific format.
 * 
 * @param envp The parameter `envp` is a pointer to an array of strings. Each string in the array
 * represents an environment variable in the form "name=value". The last element of the array is a NULL
 * pointer, indicating the end of the array.
 */
static void	handle_empty(char **envp)
{
	int	entity;
	int	i;

	entity = 0;
	while (envp[entity])
	{
		i = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp[entity][i] && envp[entity][i] != '=')
			ft_putchar_fd(envp[entity][i++], STDOUT_FILENO);
		if (envp[entity][i] == '=')
		{
			ft_putchar_fd(envp[entity][i++], STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			while (envp[entity][i])
				ft_putchar_fd(envp[entity][i++], STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		write(STDOUT_FILENO, "\n", 1);
		entity++;
	}
}

/**
 * The function `builtin_export` handles the export command in a shell program, allowing users to set
 * environment variables.
 * 
 * @param data A pointer to a structure of type t_data, which contains various data related to the
 * program.
 * @param cmd_table The `cmd_table` parameter is a pointer to a structure `t_cmd_table` which contains
 * information about the command being executed. It includes the number of arguments (`num_args`) and
 * an array of strings (`args`) representing the command and its arguments.
 */
void	builtin_export(t_data *data, t_cmd_table *cmd_table)
{
	int		i;

	data->exit_code = 0;
	if (cmd_table->num_args == 1)
		handle_empty(data->envp);
	i = 1;
	while (i < cmd_table->num_args)
	{
		if (is_invalid(cmd_table->args[i]))
		{
			if (ft_is_blank(cmd_table->args[i]) && !data->exit_code)
				ft_putendl_fd("export: not valid in this context:", 2);
			else if (!data->exit_code)
			{
				ft_putstr_fd("bash: export: `", STDERR_FILENO);
				ft_putstr_fd(cmd_table->args[i], STDERR_FILENO);
				ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			}
			data->exit_code = 1;
		}
		else if (data->cmdt_count == 1)
			handle_valid(data, cmd_table->args[i]);
		i++;
	}
}
