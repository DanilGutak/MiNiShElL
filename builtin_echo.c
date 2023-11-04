/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:23:27 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/04 18:47:07 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	is_flag(char *arg)
{
	if (!arg || !*arg || *arg != '-')
		return (1);
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (1);
		arg++;
	}
	return (0);
}

/*
	Builtin echo
	works with flag -n as well
*/
void	builtin_echo(t_data *data, t_cmd_table *cmd_table)
{
	int	new_line;
	int	i;

	new_line = is_flag(cmd_table->args[1]);
	i = ft_tr(new_line, 1, 2);
	while (i < cmd_table->num_args)
	{
		ft_putstr_fd(cmd_table->args[i], STDOUT_FILENO);
		if (i != cmd_table->num_args - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
	data->exit_code = 0;
}
