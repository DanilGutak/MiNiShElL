/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:24 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/24 11:31:34 by dgutak           ###   ########.fr       */
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

int	is_not_redir(t_token_type type)
{
	if (type == WORD || type == DQUOTE || type == DQUOTE || type == PIPE)
		return (1);
	return (0);
}

int	fill_cmd_args(t_data *data, int j, int i)
{
	int	k;

	k = 0;
	while (++i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_arg(data->tokens[i].type) && (i == 0
				|| is_not_redir(data->tokens[i - 1].type)))
		{
			data->cmdt[j].cmd = ft_strdup(data->tokens[i].value);
			if (!data->cmdt[j].cmd)
				exit_shell(data, 1);
			break ;
		}
	}
	while (++i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_arg(data->tokens[i].type) && (i == 0
				|| is_not_redir(data->tokens[i - 1].type)))
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
	printf("token_left: %d\n", data->token_count - i);
	while (i < data->token_count && data->tokens[i].type != PIPE)
	{
		if (is_arg(data->tokens[i].type) && (i == 0
				|| is_not_redir(data->tokens[i - 1].type)))
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
	printf("~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("cmdt_count: %d\n", data->cmdt_count);
	printf("~~~~~~~~~~~~~~~~~~~~~~\n");
	data->cmdt = ft_calloc(data->cmdt_count, sizeof(t_cmd_table));
	if (!data->cmdt)
		exit_shell(data, 1);
	printf("*************************\n");
	while (j < data->cmdt_count)
	{		
		data->cmdt[j].num_args = count_args(data, i) - 1;
		printf("num_args: %d\n", data->cmdt[j].num_args);
		data->cmdt[j].args = ft_calloc((data->cmdt[j].num_args),
				sizeof(char *));
		if (!data->cmdt[j].args)
			exit_shell(data, 1);
		data->cmdt[j].cmd = NULL;
		i = fill_cmd_args(data, j, i - 1) + 1;
		data->cmdt[j].fd_in = 0;
		data->cmdt[j].fd_out = 1;
		printf("-------------------\n");
		printf("cmd: {%s}\n", data->cmdt[j].cmd);
		for (int k = 0; k < data->cmdt[j].num_args; k++)
			printf("arg{%d}: {%s}\n", k, data->cmdt[j].args[k]);
		printf("-------------------\n");
		printf("*************************\n");
		j++;
	}
	return (0);
}
