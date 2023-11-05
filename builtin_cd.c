/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:12:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/05 15:21:44 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(t_data *data, char *path, char *init_pwd)
{
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: ", path);
		perror("");
		data->exit_code = 1;
		free(init_pwd);
		return (1);
	}
	if (data->cmdt_count != 1)
	{
		if (chdir(init_pwd) == -1)
		{
			ft_printf_fd(2, "minishell: cd: %s: ", init_pwd);
			perror("");
			data->exit_code = 1;
			free(init_pwd);
			return (1);
		}
		free(init_pwd);
		return (0);
	}
	if (set_variable(data, "OLDPWD", init_pwd) != 0 && ++data->exit_code)
		return (free(init_pwd), 1);
	return (0);
}

int	builtin_cd(t_data *data, t_cmd_table *cmd_table)
{
	char	*path;
	char	*temp;
	char	*init_pwd;

	data->exit_code = 0;
	if (cmd_table->num_args > 2)
		return (data->exit_code = 1, ft_printf_fd(2,
				"minishell: cd: too many arguments\n"), 1);
	init_pwd = getcwd(NULL, 0);
	if (!init_pwd)
		return (data->exit_code = 1, print_error(data, "minishell: cd:", 1));
	path = cmd_table->args[1];
	if (!path || path[0] == 0)
		return (free(init_pwd), 1);
	if (change_dir(data, path, init_pwd) != 0 || data->cmdt_count != 1)
		return (1);
	free(init_pwd);
	temp = getcwd(NULL, 0);
	if (!temp)
		return (data->exit_code = 1, print_error(data, "minishell: cd:", 1));
	if (set_variable(data, "PWD", temp) != 0)
		return (data->exit_code = 1, free(temp), 1);
	return (free(temp), 0);
}
