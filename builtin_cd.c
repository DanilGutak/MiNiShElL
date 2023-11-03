/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:12:50 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 20:24:13 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	builtin_cd(t_data *data, t_cmd_table *cmd_table)
{
	char	*path;
	char	*temp;

	data->exit_code = 0;
	if (cmd_table->num_args > 2)
		return (data->exit_code = 1, ft_printf_fd(2,
				"minishell: cd: too many arguments\n"), 1);
	path = cmd_table->args[1];
	if (!path || path[0] == 0)
		return (1);
	if (chdir(path) == -1 && ft_printf_fd(2, "minishell: cd: %s: ", path))
		return (data->exit_code = 1, perror(""), 1);
	temp = get_variable_value(data, "PWD");
	if (!temp)
		return (data->exit_code = 1, 1);
	if (set_variable(data, "OLDPWD", temp) != 0)
		return (data->exit_code = 1, free(temp), 1);
	free(temp);
	temp = NULL;
	temp = getcwd(temp, 0);
	if (!temp)
		return (data->exit_code = 1, 1);
	if (set_variable(data, "PWD", temp) != 0)
		return (data->exit_code = 1, free(temp), 1);
	free(temp);
	return (0);
}
