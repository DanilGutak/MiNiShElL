/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:04:33 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/28 17:27:05 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *str)
{
	if (*str == '-' || *str == '+' || ft_isdigit(*str) == 0)
		str++;
	else
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (1);
		str++;
	}
	ft_split(c);
	return (0);
}
void	exit2(t_data *data, t_cmd_table *cmd_table)
{
	free_all(data);
	printf("exit\n");
	if (cmd_table->num_args > 2)
	{
		printf("minishell: exit: too many arguments\n");
		data->exit_code = 1;
		return ;
	}
	else if (cmd_table->num_args == 1)
		exit(data->exit_code);
	else
	{
		if (check_arg(cmd_table->args[1]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd_table->args[1]);
			exit(255);
		}
		else
			exit(ft_atoi(cmd_table->args[1]));
	}
}
