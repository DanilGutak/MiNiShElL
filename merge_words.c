/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:05:52 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/07 14:14:18 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	proper_copy(t_token *new_tokens, int *i, int *j, char **temp)
{
	int	k;

	k = -1;
	if (*i > 0 && new_tokens[*j].no_space == 1)
	{
		*j = *j - 1;
		new_tokens[*j].value = ft_strjoin(new_tokens[*j].value, temp[++k]);
		if (!new_tokens[*j].value)
			return (1);
		*j = *j + 1;
	}
	while (temp[++k])
	{
		if (k == 1 && *j > 1 && is_not_redir(new_tokens[*j - 2].type) == 0)
			new_tokens[*j - 2].no_space = 2;
		new_tokens[*j].value = ft_strdup(temp[k]);
		if (!new_tokens[*j].value)
			return (1);
		*j = *j + 1;
	}
	return (0);
}

int	split_words(t_data *data, t_token *new_tokens, int *i, int *j)
{
	char	**temp;

	temp = ft_split(data->tokens[*i].value, ' ');
	if (!temp)
		return (print_error(data, "ft_split", 1));
	if (!temp[0])
	{
		free_double_p(temp);
		return (2);
	}
	if (proper_copy(new_tokens, i, j, temp) == 1)
	{
		free_double_p(temp);
		return (print_error(data, "malloc", 1));
	}
	free_double_p(temp);
	return (0);
}

int	copy_not_word(t_data *data, t_token *new_tokens, int *i, int *j)
{
	if (*i > 0 && new_tokens[*j].no_space == 1)
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
	return (0);
}

/* the copy tokens contents into new tokens,
	if no_space = 1 concats nex elements as well */
int	copy_token(t_data *data, t_token *new_tokens, int *i, int *j)
{
	int	ret;

	new_tokens[*j].type = data->tokens[*i].type;
	if (is_arg(data->tokens[*i].type) == 1)
	{
		if (data->tokens[*i].type == WORD)
		{
			ret = split_words(data, new_tokens, i, j);
			if (ret == 1 || ret == 2)
				return (ret % 2);
		}
		else
			if (copy_not_word(data, new_tokens, i, j) == 1)
				return (1);
		new_tokens[*j].no_space = data->tokens[*i].no_space;
	}
	else
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
	new_tokens = ft_calloc(count_new_tokens(data) + 1, sizeof(t_token));
	if (!new_tokens)
		return (print_error(data, "ft_calloc ", 1));
	while (i < data->token_count)
	{
		if (copy_token(data, new_tokens, &i, &j) == 1)
			return (free_tokens(new_tokens, -1, data));
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
