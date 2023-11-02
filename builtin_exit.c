/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:04:33 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/02 18:50:26 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

long int	atoi_new(char *str)
{
	long int	x;
	long int	sign;

	x = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\v' || *str == '\t' || *str == '\n'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			x = x * 10 + *str - '0';
		else
			break ;
		if ((x > 4294967295 && sign == 1) || (sign == -1 && x > 4294967296))
			return (9876543210);
		str++;
	}
	return (sign * x);
}

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

void	builtin_exit_part2(t_data *data, t_cmd_table *cmd_table, int code,
		int count)
{
	if (count == 1)
		ft_printf_fd(2, "exit\n");
	if (count == 1 && (!cmd_table || cmd_table->num_args == 1))
		exit(data->exit_code);
	code = atoi_new(cmd_table->args[1]);
	if (code == 987654321)
	{
		ft_printf_fd(1, "minishell: exit: %s: numeric argument required\n",
			cmd_table->args[1]);
		data->exit_code = 2;
		if (count == 1)
		{
			clean_all(data);
			exit(data->exit_code);
		}
		return ;
	}
	if (code < 0)
		data->exit_code = 256 + code % 256;
	else
		data->exit_code = code % 256;
	if (count == 1)
		clean_all(data);
	if (count == 1)
		exit(data->exit_code);
}

void	builtin_exit(t_data *data, t_cmd_table *cmd_table)
{
	int	count;

	count = data->cmdt_count;
	if (!cmd_table)
	{
		clean_all(data);
		exit(data->exit_code);
	}
	if (cmd_table && cmd_table->num_args > 1
		&& check_arg(cmd_table->args[1]) == 1)
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			cmd_table->args[1]);
		data->exit_code = 2;
		if (count == 1)
		{
			clean_all(data);
			exit(data->exit_code);
		}
		return ;
	}
	if (cmd_table && cmd_table->num_args > 2)
		return (ft_printf_fd(2, "minishell: exit: too many arguments\n"),
			(void)(data->exit_code = 1));
	builtin_exit_part2(data, cmd_table, 0, count);
}
