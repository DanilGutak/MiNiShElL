/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/30 16:17:29 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

void	execute_command(t_data *data, t_cmd_table *cmd_table)
{
	pid_t	process1;

	process1 = fork();
	if (process1 < 0)
		exit_shell(data, 1);
	if (!process1)
	{
		if (execve(cmd_table->cmd, cmd_table->args, data->envp) == -1)
		{
			ft_putstr_fd("minishell : ", 2);
			ft_putstr_fd(cmd_table->cmd, 2);
			perror(" ");
			clean_stuff(data);
			exit(1);
		}
	}
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
	int		fd[2];

	i = -1;
	while (++i < data->cmdt_count)
	{
		if (execute_builtin(data, &data->cmdt[i]) == 1 || find_executable(data,
				&data->cmdt[i]) == 1)
			continue ;
		if (pipe(fd) == -1)
			exit_shell(data, 1);
		execute_command(data, &data->cmdt[i]);
	}
	while (wait(&status) > 0)
		;
}
