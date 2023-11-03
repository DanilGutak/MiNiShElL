/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 17:43:40 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

void	set_dups(t_cmd_table *cmd_table)
{
	if (cmd_table->fd_in != -1)
		dup2(cmd_table->fd_in, STDIN_FILENO);
	if (cmd_table->fd_out != -1)
		dup2(cmd_table->fd_out, STDOUT_FILENO);
}

void	execute_command(t_data *data, t_cmd_table *cmd_table, int i,
		int *pipe_fd)
{
	cmd_table->pid = fork();
	if (cmd_table->pid < 0)
		return ((void)print_error(data, "fork", 1));
	if (!cmd_table->pid)
	{
		if (cmd_table->fd_in != -1)
		{
			dup2(cmd_table->fd_in, STDIN_FILENO);
			close(cmd_table->fd_in);
		}
		close(pipe_fd[0]);
		if (cmd_table->fd_out != -1)
			dup2(cmd_table->fd_out, STDOUT_FILENO);
		close(pipe_fd[1]);
		execve(cmd_table->cmd, cmd_table->args, data->envp);
		exit(print_error(data, cmd_table->cmd, 1));
	}
	close(pipe_fd[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
}

int	execute_builtin(t_data *data, t_cmd_table *cmd_table, int i, int *pipe_fd)
{
	int	returno;

	returno = 0;
	if (cmd_table->fd_in != -1)
	{
		dup2(cmd_table->fd_in, STDIN_FILENO);
		close(cmd_table->fd_in);
	}
	if (cmd_table->fd_out != -1)
		dup2(cmd_table->fd_out, STDOUT_FILENO);
	close(pipe_fd[1]);
	/* if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		return (builtin_echo(data, cmd_table)); */
	/*if (ft_strcmp(cmd_table->cmd, "cd") == 0)
		return (builtin_cd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
		return (builtin_pwd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "export") == 0)
		return (builtin_export(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		return (builtin_unset(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "env") == 0)
		return (builtin_env(data, cmd_table));  */
	if (ft_strcmp(cmd_table->cmd, "exit") == 0 && ++returno)
		builtin_exit(data, cmd_table);
	close(cmd_table->fd_out);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	dup2(data->original_stdout, STDOUT_FILENO);
	dup2(data->original_stdin, STDIN_FILENO);
	return (returno);
}

int	set_fd_in_out(t_data *data, t_cmd_table *cmd_table, int *fd, int i)
{
	if (cmd_table->in_file != -1)
		cmd_table->fd_in = cmd_table->in_file;
	else if (i != 0 && data->prev_fd != -1)
		cmd_table->fd_in = data->prev_fd;
	if (cmd_table->out_file != -1)
		cmd_table->fd_out = cmd_table->out_file;
	else if (i != data->cmdt_count - 1 && fd[1] != -1)
		cmd_table->fd_out = fd[1];
	return (0);
}

int	check_builtin(t_cmd_table *cmd_table)
{
	/* if (ft_strcmp(cmd_table->cmd, "echo") == 0)
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
		return (1); */
	if (ft_strcmp(cmd_table->cmd, "exit") == 0)
		return (1);
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
		else if (cmd_table->redirs[i].type == REDIR_OUT)
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
	}
	return (0);
}

void	wait_children(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->cmdt_count)
		if (data->cmdt[i].is_child_created == 1)
			waitpid(data->cmdt[i].pid, &status, 0);
	if (data->cmdt[i - 1].is_child_created == 1)
		data->exit_code = WEXITSTATUS(status);
}

int	fake_pipes(t_data *data, int i, int *pip)
{
	if (data->cmdt[i].fd_in != -1)
	{
		dup2(data->cmdt[i].fd_in, STDIN_FILENO);
		close(data->cmdt[i].fd_in);
	}
	if (data->cmdt[i].fd_out != -1)
		dup2(data->cmdt[i].fd_out, STDOUT_FILENO);
	close(pip[1]);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pip[0];
	else
		close(pip[0]);
	dup2(data->original_stdout, STDOUT_FILENO);
	dup2(data->original_stdin, STDIN_FILENO);
	return (1);
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
		if (manage_redirs(data, &data->cmdt[i]) == 1
			&& fake_pipes(data, i, pip))
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
