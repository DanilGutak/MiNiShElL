/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:24 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/25 20:13:15 by dgutak           ###   ########.fr       */
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

void	copy_token(t_data *data, t_token *new_tokens, int *i, int *j)
{
	new_tokens[*j].type = data->tokens[*i].type;
	if (is_arg(data->tokens[*i].type) == 1)
	{
		new_tokens[*j].value = ft_strdup(data->tokens[*i].value);
		if (!new_tokens[*j].value)
			exit_shell(data, 1);
		while (data->tokens[*i].no_space == 1)
		{
			*i = *i + 1;
			new_tokens[*j].value = ft_strjoin(new_tokens[*j].value,
					data->tokens[*i].value);
			if (!new_tokens[*j].value)
				exit_shell(data, 1);
		}
	}
	*j = *j + 1;
}

void	merge_words(t_data *data)
{
	t_token	*new_tokens;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	new_tokens = ft_calloc(data->token_count, sizeof(t_token));
	if (!new_tokens)
		exit_shell(data, 1);
	while (i < data->token_count)
	{
		copy_token(data, new_tokens, &i, &j);
		i++;
	}
	/* for (int k = 0; k < data->token_count; k++)
		printf("token{%d}: {%s} type: {%u} no_space: {%u}\n", k,
			data->tokens[k].value, data->tokens[k].type,
			data->tokens[k].no_space);
	for (int k = 0; k < j; k++)
		printf("new_token{%d}: {%s}\n", k, new_tokens[k].value); */
	while (++k < data->token_count)
		if (data->tokens[k].value)
			free(data->tokens[k].value);
	free(data->tokens);
	data->tokens = new_tokens;
	data->token_count = j;
	/* printf("token_count_new: %d\n", data->token_count); */
}

int	count_args(t_data *data, int i)
{
	int	count;

	count = 0;
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
	merge_words(data);
	/* for (int k = 0; k < data->token_count; k++)
		printf("token{%d}: {%s}\n", k, data->tokens[k].value); */
	data->cmdt_count = count_pipes(data) + 1;
	/* printf("~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("cmdt_count: %d\n", data->cmdt_count);
	printf("~~~~~~~~~~~~~~~~~~~~~~\n"); */
	data->cmdt = ft_calloc(data->cmdt_count, sizeof(t_cmd_table));
	if (!data->cmdt)
		exit_shell(data, 1);
	/* printf("*************************\n"); */
	while (j < data->cmdt_count)
	{
		data->cmdt[j].num_args = count_args(data, i);
		/* printf("num_args: %d\n", data->cmdt[j].num_args); */
		if (data->cmdt[j].num_args > 0)
		{
			data->cmdt[j].args = ft_calloc((data->cmdt[j].num_args + 1),
					sizeof(char *));
			if (!data->cmdt[j].args)
				exit_shell(data, 1);
		}
		else
			data->cmdt[j].args = NULL;
		data->cmdt[j].cmd = NULL;
		/* printf("-------------------\n"); */
		fill_redirs(data, j, i);
		/* for (int k = 0; k < data->cmdt[j].num_redirs; k++)
			printf("redir{%d}: {%s}, type : {%d}\n", k, data->cmdt[j].redirs[k].value,data->cmdt[j].redirs[k].type );
		if (!data->cmdt[j].redirs)
			printf("redirs: NULL\n"); */
		i = fill_cmd_args(data, j, i - 1) + 1;
		data->cmdt[j].fd_in = 0;
		data->cmdt[j].fd_out = 1;
		/* printf("cmd: {%s}\n", data->cmdt[j].cmd);
		for (int k = 0; k <= data->cmdt[j].num_args; k++)
			printf("arg{%d}: {%s}\n", k, data->cmdt[j].args[k]);
		printf("-------------------\n");
		printf("*************************\n"); */
		j++;
	}
	return (0);
}
