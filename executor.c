/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/01 19:16:08 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

void	execute_command(t_data *data, t_cmd_table *cmd_table, int i)
{

	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit_shell(data, 1);
	printf("cmd: %s\n", cmd_table->cmd);
	printf("pipe[0]: %d\n", pipe_fd[0]);
	printf("pipe[1]: %d\n", pipe_fd[1]);
	cmd_table->pid = fork();
	if (cmd_table->pid < 0)
		exit_shell(data, 1);
	if (!cmd_table->pid)
	{
		if (i != 0)
		{
			dup2(data->prev_fd, STDIN_FILENO);
			close(data->prev_fd); // Close the read end of the pipe
		}
		if (i != data->cmdt_count - 1)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]); // Close the write end of the pipe
		}
		execve(cmd_table->cmd, cmd_table->args, data->envp);
		print_error(data, cmd_table->cmd, 1);
		exit(42);
	}
	printf("closing pipe[1]: %d\n", pipe_fd[1]);
	close(pipe_fd[1]);
	printf("closing prev_fd: %d\n", data->prev_fd);
	if (data->prev_fd != -1)
		close(data->prev_fd);
	if (i != data->cmdt_count - 1)
		data->prev_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
}

int	execute_builtin(t_data *data, t_cmd_table *cmd_table)
{
	/* if (ft_strcmp(cmd_table->cmd, "echo") == 0)
		return (builtin_echo(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "cd") == 0)
		return (builtin_cd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "pwd") == 0)
		return (builtin_pwd(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "export") == 0)
		return (builtin_export(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "unset") == 0)
		return (builtin_unset(data, cmd_table));
	if (ft_strcmp(cmd_table->cmd, "env") == 0)
		return (builtin_env(data, cmd_table)); */
	if (ft_strcmp(cmd_table->cmd, "exit") == 0)
		return (builtin_exit(data, cmd_table), 1);
	return (0);
}

void	executor(t_data *data)
{
	int		i;
	int		status;

	i = -1;
	data->prev_fd = -1;
	while (++i < data->cmdt_count)
	{
		if (execute_builtin(data, &data->cmdt[i]) == 1 || find_executable(data,
				&data->cmdt[i]) == 1)
			continue ;
		data->cmdt[i].is_child_created = 1;
		execute_command(data, &data->cmdt[i], i);
		printf("pid: %d\n", data->cmdt[i].pid);
	}
	i = -1;
	while (++i < data->cmdt_count)
		waitpid(data->cmdt[i].pid, &status, 0);
	if (data->cmdt[i - 1].is_child_created == 1)
		data->exit_code = WEXITSTATUS(status);
	printf("exit_code : %d \n", data->exit_code);
}
