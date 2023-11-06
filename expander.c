/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:06:36 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/06 18:13:33 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	replace_dollar(char *iterate, char **result, t_data *data, int ex)
{
	const int	vlen = count_var_len(iterate);
	char		*buffer;
	char		*key;

	if (vlen == 1 && ex)
		return (*result = ft_strdup(""), vlen);
	if (vlen == 1)
		return (*result = ft_strdup("$"), vlen);
	key = ft_substr(iterate, 1, vlen - 1);
	if (key == NULL)
		return (vlen);
	buffer = get_variable_value(data, key);
	free(key);
	if (buffer == NULL)
		*result = ft_strdup("");
	else
		*result = ft_strdup(buffer);
	free(buffer);
	return (vlen);
}

int	concat_chars(char *iterate, char **result)
{
	int	i;

	i = 0;
	while (iterate[i] && iterate[i] != '$')
		i++;
	*result = ft_substr(iterate, 0, (size_t)i);
	return (i);
}

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

/*
in case of variable within the token, shoud replace key with its value
exceptions:
	$?
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
			ex = data->tokens[i].type == WORD && data->tokens[i + 1].type == DQUOTE && data-> tokens[i].no_space;
			if (expand_token(data->tokens[i].value, data, i, ex) == MALLOC_F)
				return (MALLOC_F);
		}
		i++;
	}
	return (SUCCESS);
}
