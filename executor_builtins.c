/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:48:57 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/06 20:17:24 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function sets up file descriptors for input and output in a built-in command, and closes a pipe
 * file descriptor.
 * 
 * @param cmd_table A pointer to a structure of type t_cmd_table, which likely contains information
 * about file descriptors for input and output.
 * @param pipe_fd The parameter `pipe_fd` is an integer array that represents the file descriptors for
 * the pipe. It is used for inter-process communication between the parent and child processes.
 * `pipe_fd[0]` is the file descriptor for reading from the pipe, and `pipe_fd[1]` is the
 */
void	setup_fd_in_builtin(t_cmd_table *cmd_table, int *pipe_fd)
{
	if (cmd_table->fd_in != -1)
	{
		dup2(cmd_table->fd_in, STDIN_FILENO);
		if (cmd_table->fd_in != -1)
			close(cmd_table->fd_in);
	}
	if (cmd_table->fd_out != -1)
		dup2(cmd_table->fd_out, STDOUT_FILENO);
	close(pipe_fd[1]);
}

void	restore_fds(t_data *data, t_cmd_table *cmd_table, int i, int *pipe_fd)
{
	if (cmd_table->fd_out != -1)
		close(cmd_table->fd_out);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	dup2(data->original_stdout, STDOUT_FILENO);
	dup2(data->original_stdin, STDIN_FILENO);
	if (cmd_table->fd_in != -1)
		close(cmd_table->fd_in);
	if (cmd_table->fd_out != -1)
		close(cmd_table->fd_out);
	if (data->cmdt[i].last_heredoc)
	{
		unlink(data->cmdt[i].last_heredoc);
		free(data->cmdt[i].last_heredoc);
	}
}

void	execute_builtin(t_data *data, t_cmd_table *cmd_table, int i, int *p_fd)
{
	setup_fd_in_builtin(cmd_table, p_fd);
	if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		builtin_echo(data, cmd_table);
	if (ft_strcmp(cmd_table->cmd, "cd") == 0)
		builtin_cd(data, cmd_table);
	if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
		builtin_pwd(data);
	if (ft_strcmp(cmd_table->cmd, "export") == 0)
		builtin_export(data, cmd_table);
	if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		builtin_unset(data, cmd_table);
	if (ft_strcmp(cmd_table->cmd, "env") == 0)
		builtin_env(data, cmd_table);
	if (ft_strcmp(cmd_table->cmd, "exit") == 0)
		builtin_exit(data, cmd_table);
	restore_fds(data, cmd_table, i, p_fd);
}

int	check_builtin(t_cmd_table *cmd_table)
{
	if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_table->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_table->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd_table->cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd_table->cmd, "exit") == 0)
		return (1);
	return (0);
}
