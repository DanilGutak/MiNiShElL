/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:11:33 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/07 13:50:03 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function checks if a command with a slash is a valid executable file or directory.
 * 
 * @param cmd_table A pointer to a structure of type t_cmd_table, which likely contains information
 * about a command being checked.
 * @param data The parameter `data` is of type `t_data`, which is a user-defined data structure. It
 * likely contains information and variables related to the overall state and execution of the program.
 * 
 * @return an integer value.
 */
int	check_with_slash(t_cmd_table *cmd_table, t_data *data)
{
	DIR	*dir;

	if (access(cmd_table->cmd, F_OK) == 0)
	{
		dir = opendir(cmd_table->cmd);
		if (dir)
		{
			ft_printf_fd(2, "minishell: %s: Is a directory\n", cmd_table->cmd);
			data->exit_code = 126;
			closedir(dir);
		}
		else if (access(cmd_table->cmd, X_OK) == 0)
			return (0);
		else
		{
			ft_printf_fd(2, "minishell: %s: Permission denied\n",
				cmd_table->cmd);
			data->exit_code = 126;
		}
		return (1);
	}
	ft_printf_fd(2, "minishell: %s: No such file or directory\n",
		cmd_table->cmd);
	data->exit_code = 127;
	return (1);
}


/**
 * The function `search_in_path` searches for a command in the directories specified in the
 * `data->path` array and updates the `cmd_table->cmd` with the full path of the command if found.
 * 
 * @param data A pointer to a structure of type t_data, which contains some data related to the
 * program.
 * @param cmd_table A structure that contains information about the command being searched for. It
 * includes a field called "cmd" which is a string representing the command name.
 * @param i The variable `i` is used as an index to iterate through the `data->path` array. It is
 * incremented in each iteration of the while loop.
 * 
 * @return an integer value.
 */
int	search_in_path(t_data *data, t_cmd_table *cmd_table, int i)
{
	char	*ret;
	char	*temp;

	while (data->path && data->path[++i])
	{
		if (cmd_table->cmd[0] == '\0')
			break ;
		temp = ft_strdup(data->path[i]);
		if (!temp)
			return (print_error(data, "ft_strdup", 1) + 1);
		temp = ft_strjoin(temp, "/");
		if (!temp)
			return (print_error(data, "ft_strjoin", 1) + 1);
		ret = ft_strjoin(temp, cmd_table->cmd);
		if (!ret)
			return (print_error(data, "ft_strjoin", 1) + 1);
		if (access(ret, X_OK) == 0)
		{
			temp = cmd_table->cmd;
			cmd_table->cmd = ret;
			return (free(temp), 0);
		}
		free(ret);
	}
	return (look_in_dir(data, cmd_table));
}

/**
 * The function searches for a command in the given directory paths and checks if it exists and has the
 * necessary permissions.
 * 
 * @param data A pointer to a structure of type t_data, which contains various data related to the
 * program.
 * @param cmd_table A structure that contains information about the command being searched for, such as
 * the command itself (cmd_table->cmd) and other details.
 * @param i The variable "i" is an integer used as an index in a loop. It is incremented in each
 * iteration of the loop to iterate through the elements of the "data->path" array.
 * 
 * @return an integer value.
 */
int	search_if_exist(t_data *data, t_cmd_table *cmd_table, int i)
{
	char	*ret;
	char	*temp;

	while (data->path && data->path[++i])
	{
		temp = ft_strdup(data->path[i]);
		if (!temp)
			return (print_error(data, "ft_strdup", 1) + 1);
		ret = ft_strjoin(temp, cmd_table->cmd);
		if (!ret)
			return (print_error(data, "ft_strjoin", 1) + 1);
		if (access(ret, F_OK) == 0)
		{
			temp = cmd_table->cmd;
			cmd_table->cmd = ret;
			free(temp);
			ft_printf_fd(2, "minishell: %s: Permission denied\n",
				cmd_table->cmd);
			data->exit_code = 126;
			return (0);
		}
		free(ret);
	}
	return (exist_in_dir(data, cmd_table));
}

/**
 * The function `find_executable` checks if a command is executable and returns an appropriate exit
 * code.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param cmd_table The `cmd_table` parameter is a pointer to a structure of type `t_cmd_table`.
 * 
 * @return The function `find_executable` returns an integer value.
 */
int	find_executable(t_data *data, t_cmd_table *cmd_table)
{
	int	i;
	int	ret;

	i = -1;
	if (!cmd_table->cmd)
		return (1);
	if (cmd_table->cmd[0] == '\0')
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd_table->cmd);
		data->exit_code = 127;
		return (1);
	}
	if (ft_strchr(cmd_table->cmd, '/') != 0 || cmd_table->cmd[0] == '.')
		return (check_with_slash(cmd_table, data));
	ret = search_in_path(data, cmd_table, i);
	if (ret == 0)
		return (0);
	else if (ret == 2)
		return (1);
	if (search_if_exist(data, cmd_table, i) == 1)
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd_table->cmd);
		data->exit_code = 127;
	}
	return (1);
}
