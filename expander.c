/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:06:36 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/06 20:38:39 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function counts the length of a variable in a string, starting from a given position.
 * 
 * @param value The parameter "value" is a pointer to a constant character array (string).
 * 
 * @return the length of a variable in the given string.
 */
int	count_var_len(const char *value)
{
	int	i;

	i = 1;
	if (value[i] == '?')
		return (2);
	while (value[i] == '_' || ft_isalnum(value[i]))
		i++;
	return (i);
}

/**
 * The function `concat_chars` takes a string `iterate` and a double pointer `result`, and returns the
 * length of the substring before the first occurrence of '$' in `iterate`, while also assigning the
 * substring to `result`.
 * 
 * @param iterate A pointer to a character array (string) that we want to iterate through.
 * @param result The "result" parameter is a pointer to a pointer to a character. It is used to store
 * the result of concatenating characters from the "iterate" string.
 * 
 * @return the length of the substring that was extracted from the "iterate" string.
 */
int	concat_chars(char *iterate, char **result)
{
	int	i;

	i = 0;
	while (iterate[i] && iterate[i] != '$')
		i++;
	*result = ft_substr(iterate, 0, (size_t)i);
	return (i);
}

/**
 * The function `expand_token` takes a string `value`, a pointer to a `t_data` struct `data`, an
 * integer `t`, and an integer `ex`, and expands any variables or special characters in `value` using
 * the information in `data`, storing the result in `data->tokens[t].value`.
 * 
 * @param value A pointer to a character array representing a token value.
 * @param data A pointer to a structure of type t_data.
 * @param t The parameter "t" is an integer that represents the index of the token in the data
 * structure.
 * @param ex The parameter "ex" is an integer that represents the index of the current expansion being
 * performed.
 * 
 * @return either `MALLOC_F` or `SUCCESS`.
 */
static int	expand_token(char *value, t_data *data, int t, int ex)
{
	char	*buf_value;
	char	*buf_res;
	char	*buffer;
	char	*res;

	res = NULL;
	buf_value = value;
	while (*value)
	{
		buffer = NULL;
		if (*value == '$')
			value += replace_dollar(value, &buffer, data, ex);
		else
			value += concat_chars(value, &buffer);
		if (buffer == NULL)
			return (free(res), MALLOC_F);
		buf_res = ft_strcat(res, buffer);
		(free(buffer), free(res));
		if (buf_res == NULL)
			return (MALLOC_F);
		res = buf_res;
	}
	free(buf_value);
	data->tokens[t].value = res;
	return (SUCCESS);
}

/**
 * The function `is_exception` checks if a token in a given data structure is an exception based on
 * certain conditions.
 * 
 * @param data A pointer to a struct of type t_data, which contains information about tokens.
 * @param i The parameter `i` is an integer representing the index of a token in the `data->tokens`
 * array.
 * 
 * @return a boolean value (1 or 0) indicating whether the given condition is true or false.
 */
int	is_exception(t_data *data, int i)
{
	return (data->tokens[i].type == WORD
		&& i + 1 < data->token_count
		&& data->tokens[i + 1].type != WORD
		&& data-> tokens[i].no_space
		&& ft_strlen(data->tokens[i].value) == 1);
}

/*
in case of variable within the token, shoud replace key with its value
exceptions:
	$?
*/
/**
 * The function `expander` expands tokens in a given data structure by checking for variables and
 * expanding them if necessary.
 * 
 * @param data A pointer to a struct of type t_data, which contains information about the tokens and
 * their types.
 * 
 * @return either `MALLOC_F` or `SUCCESS`.
 */
int	expander(t_data *data)
{
	int	end;
	int	i;
	int	ex;

	i = 0;
	end = data->token_count;
	while (i < end)
	{
		if (data->tokens[i].type == REDIR_HEREDOC)
		{
			i += 2;
			while (data->tokens[i].no_space)
				i++;
		}
		if ((data->tokens[i].type == WORD || data->tokens[i].type == DQUOTE)
			&& ft_contains(data->tokens[i].value, '$'))
		{
			ex = is_exception(data, i);
			if (expand_token(data->tokens[i].value, data, i, ex) == MALLOC_F)
				return (MALLOC_F);
		}
		i++;
	}
	return (SUCCESS);
}
