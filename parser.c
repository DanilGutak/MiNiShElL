/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:24 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 11:51:53 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* the copy tokens contents into new tokens,
	if no_space = 1 concats nex elements as well */
int	copy_token(t_data *data, t_token *new_tokens, int *i, int *j)
{
	new_tokens[*j].type = data->tokens[*i].type;
	if (is_arg(data->tokens[*i].type) == 1)
	{
		new_tokens[*j].value = ft_strdup(data->tokens[*i].value);
		if (!new_tokens[*j].value)
			return (print_error(data, "ft_strdup", 1));
		while (data->tokens[*i].no_space == 1)
		{
			*i = *i + 1;
			new_tokens[*j].value = ft_strjoin(new_tokens[*j].value,
					data->tokens[*i].value);
			if (!new_tokens[*j].value)
				return (print_error(data, "ft_strjoin", 1));
		}
	}
	*j = *j + 1;
	return (0);
}

int	merge_words(t_data *data)
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
		return (print_error(data, "ft_calloc ", 1));
	while (i < data->token_count)
	{
		if (copy_token(data, new_tokens, &i, &j) == 1)
			return (1);
		i++;
	}
	while (++k < data->token_count)
		if (data->tokens[k].value)
			free(data->tokens[k].value);
	free(data->tokens);
	data->tokens = new_tokens;
	data->token_count = j;
	return (0);
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

/* transforms tokens into cmd tables.
merges words with no_spaces
create cmd table for each pipe
fill cmd, args and redirs in cmd table
 */
int	fill_cmdt(t_data *data, int j, int *i)
{
	data->cmdt[j].num_args = count_args(data, *i);
	if (data->cmdt[j].num_args > 0)
	{
		data->cmdt[j].args = ft_calloc((data->cmdt[j].num_args + 1),
				sizeof(char *));
		if (!data->cmdt[j].args)
			return (print_error(data, "ft_calloc error", 1));
	}
	else
		data->cmdt[j].args = NULL;
	data->cmdt[j].cmd = NULL;
	data->cmdt[j].is_child_created = 0;
	data->cmdt[j].pid = 0;
	data->cmdt[j].fd_in = -1;
	data->cmdt[j].fd_out = -1;
	data->cmdt[j].in_file = -1;
	data->cmdt[j].out_file = -1;
	if (fill_redirs(data, j, *i) == 1)
		return (1);
	*i = fill_cmd_args(data, j, *i - 1) + 1;
	if (*i == 0)
		return (1);
	return (0);
}

int	parser(t_data *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (merge_words(data) == 1)
		return (1);
	data->cmdt_count = count_pipes(data) + 1;
	data->cmdt = ft_calloc(data->cmdt_count, sizeof(t_cmd_table));
	if (!data->cmdt)
		return (print_error(data, "ft_calloc error", 1));
	while (j < data->cmdt_count)
	{
		if (fill_cmdt(data, j, &i))
			return (1);
		j++;
	}
	return (0);
}
