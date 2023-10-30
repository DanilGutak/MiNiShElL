/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:11:33 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/30 13:11:09 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	check_with_slash(t_cmd_table *cmd_table)
{
	DIR	*dir;

	if (access(cmd_table->cmd, F_OK) == 0)
	{
		dir = opendir(cmd_table->cmd);
		if (dir)
		{
			ft_printf_fd(2, "minishell: %s: Is a directory.\n", cmd_table->cmd);
			closedir(dir);
		}
		else if (access(cmd_table->cmd, X_OK) == 0)
			return (0);
		else
			ft_printf_fd(2, "minishell: %s: Permission denied\n",
				cmd_table->cmd);
	}
	else
		ft_printf_fd(2, "minishell: %s: No such file or directory\n",
			cmd_table->cmd);
	return (1);
}

/* tries to find the command to execute,
	better explanation of bash logic is in README
but if slash is present tries to run command as it is,
	otherwise tries to connect with dirs from PAtTH */
int	search_in_path(t_data *data, t_cmd_table *cmd_table, int i)
{
	char	*ret;
	char	*temp;

	while (data->path[++i])
	{
		if (cmd_table->cmd[0] == '\0')
			break ;
		temp = ft_strdup(data->path[i]);
		if (!temp)
			exit_shell(data, 1);
		ret = ft_strjoin(temp, cmd_table->cmd);
		if (!temp)
			free(temp);
		if (!ret)
			exit_shell(data, 1);
		if (access(ret, X_OK) == 0)
		{
			temp = cmd_table->cmd;
			cmd_table->cmd = ret;
			free(temp);
			return (0);
		}
		free(ret);
	}
	return (1);
}

int	search_if_exist(t_data *data, t_cmd_table *cmd_table, int i)
{
	char	*ret;
	char	*temp;

	while (data->path[++i])
	{
		temp = ft_strdup(data->path[i]);
		if (!temp)
			exit_shell(data, 1);
		ret = ft_strjoin(temp, cmd_table->cmd);
		if (!ret)
			exit_shell(data, 1);
		if (access(ret, F_OK) == 0)
		{
			temp = cmd_table->cmd;
			cmd_table->cmd = ret;
			free(temp);
			ft_printf_fd(2, "minishell: %s: Permission denied\n",
				cmd_table->cmd);
			return (0);
		}
		free(ret);
	}
	return (1);
}
int	find_executable(t_data *data, t_cmd_table *cmd_table)
{
	int	i;

	i = -1;
	if (!cmd_table->cmd)
		return (1);
	if (cmd_table->cmd[0] == '\0')
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd_table->cmd);
		return (1);
	}
	if (ft_strchr(cmd_table->cmd, '/') != 0)
		return (check_with_slash(cmd_table));
	if (search_in_path(data, cmd_table, i) == 0)
		return (0);
	if (search_if_exist(data, cmd_table, i) == 1)
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd_table->cmd);
	return (1);
}