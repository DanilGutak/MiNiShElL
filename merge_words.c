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

/**
 * The function `proper_copy` copies values from a temporary array `temp` into a `t_token` array
 * `new_tokens`, with some additional logic for handling spaces and redirections.
 * 
 * @param new_tokens A pointer to an array of t_token structures.
 * @param i A pointer to an integer variable.
 * @param j The parameter `j` is a pointer to an integer. It is used as an index to access elements in
 * the `new_tokens` array.
 * @param temp A double pointer to a character array (string array) that contains the values to be
 * copied into the `new_tokens` array.
 * 
 * @return an integer value.
 */
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

/**
 * The function "split_words" splits a string into individual words and stores them in a new array of
 * tokens.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param new_tokens A pointer to an array of t_token structures.
 * @param i The parameter `i` is a pointer to an integer variable.
 * @param j The parameter `j` is a pointer to an integer. It is used to keep track of the current index
 * in the `new_tokens` array where the split words should be stored.
 * 
 * @return an integer value. The possible return values are:
 * - 0: indicating successful execution
 * - 1: indicating an error occurred during memory allocation
 * - 2: indicating that the split resulted in an empty array
 */
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

/**
 * The function `copy_not_word` copies a token's value to a new array of tokens, either by
 * concatenating it with the previous token's value or by creating a new string.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param new_tokens An array of t_token structures.
 * @param i The parameter `i` is a pointer to an integer variable.
 * @param j The parameter `j` is a pointer to an integer variable.
 * 
 * @return an integer value.
 */
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
/**
 * The function `copy_token` copies a token from the `data` structure to the `new_tokens` array,
 * handling different types of tokens and splitting words if necessary.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param new_tokens A pointer to an array of t_token structures, where the copied token will be
 * stored.
 * @param i The parameter `i` is a pointer to an integer variable. It is used as an index to access
 * elements in the `data->tokens` array.
 * @param j The parameter "j" is a pointer to an integer variable. It is used to keep track of the
 * current index in the new_tokens array where the token should be copied.
 * 
 * @return an integer value.
 */
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

/**
 * The function "merge_words" merges consecutive tokens with the same type into a single token.
 * 
 * @param data A pointer to a structure of type t_data, which contains information about the tokens and
 * their count.
 * 
 * @return an integer value.
 */
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
