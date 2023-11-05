/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:49:24 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/05 21:53:59 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <iso646.h>

int	smart_token_copy(t_data *data, t_token *new_tokens, int *i, int *j)
{
	int		k;
	char	**temp;

	if (data->tokens[*i].type == WORD)
	{
		k = -1;
		temp = ft_split(data->tokens[*i].value, ' ');
		if (!temp)
			return (print_error(data, "ft_split", 1));
		if (data->tokens[*(i - 1)].no_space)
		{
			new_tokens[*j].value = ft_strdup(data->tokens[*i].value);
			if (!new_tokens[*j].value)
				return (print_error(data, "ft_strdup", 1));
			*j = *j + 1;
		}
		while (temp[++k])
		{
			*j = *j + 1;
			new_tokens[*j].value = ft_strdup(*temp);
			if (!new_tokens[*j].value)
				return (print_error(data, "ft_strdup", 1));
		}
		free_double_p(temp);
	}
	return (0);
}

/* the copy tokens contents into new tokens,
	if no_space = 1 concats nex elements as well */
int	copy_token(t_data *data, t_token *new_tokens, int *i, int *j)
{
	int		k;
	char	**temp;

	new_tokens[*j].type = data->tokens[*i].type;
	if (is_arg(data->tokens[*i].type) == 1)
	{
		if (data->tokens[*i].type == WORD)
		{
			k = -1;
			temp = ft_split(data->tokens[*i].value, ' ');
			if (!temp)
				return (print_error(data, "ft_split", 1));
			if (!temp[0])
			{
				free_double_p(temp);
				return (0);
			}
			if (i > 0 && new_tokens[*j].no_space == 1)
			{
				*j = *j - 1;
				new_tokens[*j].value = ft_strjoin(new_tokens[*j].value,
						temp[++k]);
				if (!new_tokens[*j].value)
					return (print_error(data, "ft_strjoin", 1));
				*j = *j + 1;
			}
			while (temp[++k])
			{
				if (k == 1 && *j > 1 && is_not_redir(new_tokens[*j
							- 2].type) == 0)
					new_tokens[*j - 2].no_space = 2;
				new_tokens[*j].value = ft_strdup(temp[k]);
				if (!new_tokens[*j].value)
					return (print_error(data, "ft_strdup", 1));
				*j = *j + 1;
			}
			free_double_p(temp);
		}
		else
		{
			if (i > 0 && new_tokens[*j].no_space == 1)
			{
				*j = *j - 1;
				new_tokens[*j].value = ft_strjoin(new_tokens[*j].value,
						data->tokens[*i].value);
				if (!new_tokens[*j].value)
					return (print_error(data, "ft_strjoin", 1));
			}
			else
			{
				new_tokens[*j].value = ft_strdup(data->tokens[*i].value);
				if (!new_tokens[*j].value)
					return (print_error(data, "ft_strdup", 1));
			}
			*j = *j + 1;
		}
		new_tokens[*j].no_space = data->tokens[*i].no_space;
	}
	else
		*j = *j + 1;
	return (0);
}

int	count_new_tokens(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < data->token_count)
	{
		if (data->tokens[i].type == WORD)
		{
			j = 0;
			while (data->tokens[i].value[j])
			{
				if (data->tokens[i].value[j] == ' ')
					k++;
				j++;
			}
		}
		k++;
		i++;
	}
	return (k);
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
	new_tokens = ft_calloc(count_new_tokens(data) + 1, sizeof(t_token));
	if (!new_tokens)
		return (print_error(data, "ft_calloc ", 1));
	/* for (int i = 0; i < data->token_count; i++)
	{
		printf("data->tokens[%d].value = %s\n", i, data->tokens[i].value);
		printf("data->tokens[%d].type = %d\n", i, data->tokens[i].type);
		printf("data->tokens[%d].no_space = %d\n", i, data->tokens[i].no_space);
	} */
	while (i < data->token_count)
	{
		if (copy_token(data, new_tokens, &i, &j) == 1)
			return (1);
		i++;
	}
	/* 	for (int i = 0; i < j; i++)
		{
			printf("new_tokens[%d].value = %s\n", i, new_tokens[i].value);
			printf("new_tokens[%d].type = %d\n", i, new_tokens[i].type);
			printf("new_tokens[%d].no_space = %d\n", i, new_tokens[i].no_space);
			printf("--------------------\n");
		} */
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
