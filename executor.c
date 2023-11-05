/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/05 16:23:02 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_data *data, t_cmd_table *cmd_table, int i,
		int *pipe_fd)
{
	cmd_table->pid = fork();
	if (cmd_table->pid < 0)
		return ((void)print_error(data, "fork", 1));
	if (!cmd_table->pid)
	{
		if (cmd_table->fd_in != -1 && dup2(cmd_table->fd_in, STDIN_FILENO))
			close(cmd_table->fd_in);
		close(pipe_fd[0]);
		if (cmd_table->fd_out != -1)
			dup2(cmd_table->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
		mode(data, CHILD);
		execve(cmd_table->cmd, cmd_table->args, data->envp);
		print_error(data, cmd_table->cmd, 1);
		clean_all(data);
		exit(1);
	}
	close(pipe_fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
}

int	other_redirs(t_data *data, t_cmd_table *cmd_table, int i)
{
	if (cmd_table->redirs[i].type == REDIR_OUT)
	{
		if (cmd_table->out_file != -1)
			close(cmd_table->out_file);
		cmd_table->out_file = open(cmd_table->redirs[i].value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd_table->out_file == -1)
			return (print_error(data, cmd_table->redirs[i].value, 1));
	}
	else if (cmd_table->redirs[i].type == REDIR_APPEND)
	{
		if (cmd_table->out_file != -1)
			close(cmd_table->out_file);
		cmd_table->out_file = open(cmd_table->redirs[i].value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd_table->out_file == -1)
			return (print_error(data, cmd_table->redirs[i].value, 1));
	}
	else if (cmd_table->redirs[i].type == REDIR_HEREDOC)
	{
		do_heredoc(data, cmd_table, i);
		return (0);
	}
	return (0);
}

int	manage_redirs(t_data *data, t_cmd_table *cmd_table)
{
	int	i;

	i = -1;
	while (++i < cmd_table->num_redirs)
	{
		if (cmd_table->redirs[i].type == REDIR_IN)
		{
			if (cmd_table->in_file != -1)
				close(cmd_table->in_file);
			cmd_table->in_file = open(cmd_table->redirs[i].value, O_RDONLY);
			if (cmd_table->in_file == -1)
				return (print_error(data, cmd_table->redirs[i].value, 1));
		}
		else
			if (other_redirs(data, cmd_table, i) == 1)
				return (1);
	}
	return (0);
}

void	executor(t_data *data)
{
	int	i;
	int	pip[2];

	i = -1;
	data->prev_fd = -1;
	while (++i < data->cmdt_count)
	{
		if (pipe(pip) == -1)
			return ((void)print_error(data, "pipe", 1));
		if (manage_redirs(data, &data->cmdt[i]) == 1 && fake_pipes(data, i,
				pip))
			continue ;
		set_fd_in_out(data, &data->cmdt[i], pip, i);
		if (check_builtin(&data->cmdt[i]) == 1)
			execute_builtin(data, &data->cmdt[i], i, pip);
		else
		{
			if (find_executable(data, &data->cmdt[i]) == 0
				&& ++data->cmdt[i].is_child_created)
				execute_command(data, &data->cmdt[i], i, pip);
			else
				fake_pipes(data, i, pip);
		}
	}
	wait_children(data);
}
