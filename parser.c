/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:24 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/23 18:00:42 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < data->token_count)
		if (data->tokens[i].type == PIPE)
			j++;
	return (j);
}

int	is_arg(t_token_type type)
{
	if (type == WORD || type == DQUOTE || type == DQUOTE)
		return (1);
	return (0);
}

int	fill_cmd_args(t_data *data, int j, int i)
{
	int	k;

	k = 0;
	while (data->tokens[++i].type != PIPE && i < data->token_count)
	{
		if (is_arg(data->tokens[i].type) && (i == 0 || is_arg(data->tokens[i
						- 1].type)))
		{
			data->cmdt[j].cmd = ft_strdup(data->tokens[i].value);
			if (!data->cmdt[j].cmd)
				exit_shell(data, 1);
			break ;
		}
	}
	while (data->tokens[++i].type != PIPE && i < data->token_count)
	{
		if (is_arg(data->tokens[i].type) && (i == 0 || is_arg(data->tokens[i
						- 1].type)))
		{
			data->cmdt[j].args[k++] = ft_strdup(data->tokens[i].value);
			if (!data->cmdt[j].args[k - 1])
				exit_shell(data, 1);
		}
	}
	return (i);
}

int	count_args(t_data *data, int i)
{
	int	count;

	count = 0;
	printf("i: %d\n", i);
	printf("type: %d\n", data->tokens[i].type == PIPE);
	printf("token_count: %d\n", data->token_count);
	printf("token: {%s}\n", data->tokens[i].value);
	while (data->tokens[i].type != PIPE && i < data->token_count)
	{
		if (is_arg(data->tokens[i].type) && (i == 0 || is_arg(data->tokens[i
						- 1].type)))
			count++;
		i++;
	}
	return (count);
}

int	parser(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	data->cmdt_count = count_pipes(data) + 1;
	printf("cmdt_count: %d\n", data->cmdt_count);
	data->cmdt = ft_calloc(data->cmdt_count, sizeof(t_cmd_table));
	if (!data->cmdt)
		exit_shell(data, 1);
	while (j < data->cmdt_count)
	{
		printf("j: %d\n", j);
		data->cmdt[j].num_args = count_args(data, i) - 1;
		printf("num_args: %d\n", data->cmdt[j].num_args);
		data->cmdt[j].args = ft_calloc((data->cmdt[j].num_args + 1), sizeof(char *));
		if (!data->cmdt[j].args)
			exit_shell(data, 1);
		data->cmdt[j].cmd = NULL;
		data->cmdt[j].args = NULL;
		i = i + fill_cmd_args(data, j, i - 1) + 1;
		data->cmdt[j].fd_in = 0;
		data->cmdt[j].fd_out = 1;
		printf("cmd: {%s}\n", data->cmdt[j].cmd);
		for (int k = 0; k < data->cmdt[j].num_args; k++)
			printf("arg: {%s}\n", data->cmdt[j].args[k]);
		j++;
	}
	return (0);
}
