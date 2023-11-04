/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:38:28 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 01:15:36 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	is_invalid(char *str)
{
	if (str == NULL || !(ft_isalpha(*str) || *str == '_'))
		return (1);
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (1);
		str++;
	}
	return (0);
}

static void	handle_valid(t_data *data, char *line)
{
	char	*value;
	char	*key;
	int		i;

	if (!line || !*line || !ft_contains(line, '='))
		return ;
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	key = ft_substr(line, 0, i++);
	if (!key)
		return ;
	while (line[i])
		i++;
	value = ft_substr(line, ft_strlen(key) + 1, i);
	if (!value)
		return ;
	set_variable(data, key, value);
	free(value);
	free(key);
}

static void	handle_empty(char **envp)
{
	int	entity;
	int	i;

	entity = 0;
	while (envp[entity])
	{
		i = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (envp[entity][i] && envp[entity][i] != '=')
			ft_putchar_fd(envp[entity][i++], STDOUT_FILENO);
		if (envp[entity][i] == '=')
		{
			ft_putchar_fd(envp[entity][i++], STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			while (envp[entity][i])
				ft_putchar_fd(envp[entity][i++], STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		write(STDOUT_FILENO, "\n", 1);
		entity++;
	}
}

void	builtin_export(t_data *data, t_cmd_table *cmd_table)
{
	int		i;

	data->exit_code = 0;
	if (cmd_table->num_args == 1)
		handle_empty(data->envp);
	i = 1;
	while (i < cmd_table->num_args)
	{
		if (is_invalid(cmd_table->args[i]))
		{
			if (ft_is_blank(cmd_table->args[i]) && !data->exit_code)
				ft_putendl_fd("export: not valid in this context:", 2);
			else if (!ft_is_blank(cmd_table->args[i]) && data->exit_code)
			{
				ft_putstr_fd("bash: export: `", STDERR_FILENO);
				ft_putstr_fd(cmd_table->args[i], STDERR_FILENO);
				ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			}
			data->exit_code = 1;
		}
		else
			handle_valid(data, cmd_table->args[i]);
		i++;
	}
}
