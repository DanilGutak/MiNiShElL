/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:04:33 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/30 11:45:46 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	check_arg(char *str)
{
	if (*str == '-' || *str == '+' || ft_isdigit(*str) == 1)
		str++;
	else
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		str++;
	}
	return (0);
}

void	builtin_exit(t_data *data, t_cmd_table *cmd_table)
{
	int	code;

	if (!cmd_table)
		exit(data->exit_code);
	if (cmd_table && cmd_table->num_args > 2)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		data->exit_code = 1;
		return ;
	}
	if (cmd_table->num_args > 1 && check_arg(cmd_table->args[1]) == 1)
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			cmd_table->args[1]);
		clean_stuff(data);
		exit(2);
	}
	if (data->cmdt_count == 1)
		ft_printf_fd(2, "exit\n");
	if (!cmd_table || cmd_table->num_args == 1)
		exit(data->exit_code);
	code = ft_atoi(cmd_table->args[1]);
	clean_stuff(data);
	if (code < 0)
		exit(256 + code % 256);
	exit(code % 256);
}
