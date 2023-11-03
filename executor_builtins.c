/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:48:57 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 19:30:38 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_fd_in_builtin(t_cmd_table *cmd_table, int *pipe_fd)
{
	if (cmd_table->fd_in != -1)
	{
		dup2(cmd_table->fd_in, STDIN_FILENO);
		close(cmd_table->fd_in);
	}
	if (cmd_table->fd_out != -1)
		dup2(cmd_table->fd_out, STDOUT_FILENO);
	close(pipe_fd[1]);
}

void	restore_fds(t_data *data, t_cmd_table *cmd_table, int i, int *pipe_fd)
{
	close(cmd_table->fd_out);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	dup2(data->original_stdout, STDOUT_FILENO);
	dup2(data->original_stdin, STDIN_FILENO);
}

void	execute_builtin(t_data *data, t_cmd_table *cmd_table, int i, int *pipe_fd)
{
	setup_fd_in_builtin(cmd_table, pipe_fd);
	if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		builtin_echo(data, cmd_table);
	/*if (ft_strcmp(cmd_table->cmd, "cd") == 0)
		return (builtin_cd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
		return (builtin_pwd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "export") == 0)
		return (builtin_export(data, cmd_table));*/
	if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		builtin_unset(data, cmd_table);
	/*if (ft_strcmp(cmd_table->cmd, "env") == 0)
		return (builtin_env(data, cmd_table));  */
	if (ft_strcmp(cmd_table->cmd, "exit") == 0)
		builtin_exit(data, cmd_table);
	restore_fds(data, cmd_table, i, pipe_fd);
}

int	check_builtin(t_cmd_table *cmd_table)
{
	if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		return (1);
	//if (ft_strcmp(cmd_table->cmd, "cd") == 0)
	//	return (1);
	//if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
	//	return (1);
	//if (ft_strcmp(cmd_table->cmd, "export") == 0)
	//	return (1);
	if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		return (1);
	/*if (ft_strcmp(cmd_table->cmd, "env") == 0)
		return (1); */
	if (ft_strcmp(cmd_table->cmd, "exit") == 0)
		return (1);
	return (0);
}
