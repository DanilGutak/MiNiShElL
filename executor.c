/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:09:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/29 16:16:45 by vfrants          ###   ########.fr       */
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
			printf("minishell: %s: Is a directory.\n", cmd_table->cmd);
			closedir(dir);
		}
		else if (access(cmd_table->cmd, X_OK) == 0)
			return (0);
		else
			printf("minishell: %s: Permission denied\n", cmd_table->cmd);
	}
	else
		printf("minishell: %s: No such file or directory\n", cmd_table->cmd);
	return (1);
}

/* tries to find the command to execute,
	better explanation of bash logic is in README
but if slash is present tries to run command as it is,
	otherwise tries to connect with dirs from PAtTH */
int	find_executable(t_data *data, t_cmd_table *cmd_table)
{
	char	*ret;
	char	*temp;
	int		i;

	i = 0;
	if (!cmd_table->cmd || !*cmd_table->cmd)
		return (1);
	if (ft_strchr(cmd_table->cmd, '/') != 0)
		return (check_with_slash(cmd_table));
	while (data->path[i])
	{
		temp = ft_strdup(data->path[i]);
		if (!temp)
			exit_shell(data, 1);
		ret = ft_strjoin(temp, cmd_table->cmd);
		if (!temp)
			free(temp);
		if (!ret)
			exit_shell(data, 1);
		if (access(ret, 0) == 0)
		{
			temp = cmd_table->cmd;
			cmd_table->cmd = ret;
			free(temp);
			return (0);
		}
		free(ret);
		i++;
	}
	printf("minishell: %s: command not found\n", cmd_table->cmd);
	return (1);
}
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
			// here the custom handler for "permission denied"
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
	int	i;

	i = -1;

	for (int i = 0; data->envp[i]; i++) {
		ft_printf_fd(1, "|%s|\n", data->envp[i]);
	}
		ft_printf_fd(1, "|%s|\n", data->envp[i]);


	while (++i < data->cmdt_count)
	{
		if (execute_builtin(data, &data->cmdt[i]) == 1 || find_executable(data,
				&data->cmdt[i]) == 1)
			continue ;
		execute_command(data, &data->cmdt[i]);
	}
	wait(NULL);
}
