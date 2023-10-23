/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:09:06 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/23 17:43:46 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_redir(t_data *data, char const *s)
{
	int	ret;

	ret = 1;
	data->token_count++;
	if (*s == '<')
	{
		data->tokens[data->token_count - 1].type = REDIR_IN;
		if (*(s + 1) == '<' && ret++)
			data->tokens[data->token_count - 1].type = REDIR_HEREDOC;
	}
	else if (*s == '>')
	{
		data->tokens[data->token_count - 1].type = REDIR_OUT;
		if (*(s + 1) == '>' && ret++)
			data->tokens[data->token_count - 1].type = REDIR_APPEND;
	}
	return (ret);
}

const char	*g_token_type_names[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT",
		"REDIR_APPEND", "REDIR_HEREDOC", "DQUOTE", "SQUOTE"};

int	check_syntax_dir2(t_data *data, int i)
{
	if (data->tokens[i].type == REDIR_APPEND
		&& (data->tokens[i - 1].type != WORD
			&& data->tokens[i - 1].type != DQUOTE && i != 0
			&& data->tokens[i - 1].type != SQUOTE
			&& data->tokens[i - 1].type != PIPE))
		return (data->exit_code = 2, syntax_error(">>"), 1);
	else if (data->tokens[i].type == REDIR_HEREDOC
		&& (data->tokens[i - 1].type != WORD
			&& data->tokens[i - 1].type != DQUOTE && i != 0
			&& data->tokens[i - 1].type != SQUOTE
			&& data->tokens[i - 1].type != PIPE))
		return (data->exit_code = 2, syntax_error("<<"), 1);
	else if (data->tokens[i].type == REDIR_IN && i != 0
		&& (data->tokens[i - 1].type != WORD
			&& data->tokens[i - 1].type != DQUOTE
			&& data->tokens[i - 1].type != SQUOTE
			&& data->tokens[i - 1].type != PIPE))
		return (data->exit_code = 2, syntax_error("<"), 1);
	else if (data->tokens[i].type == REDIR_OUT && i != 0
		&& (data->tokens[i - 1].type != WORD
			&& data->tokens[i - 1].type != DQUOTE
			&& data->tokens[i - 1].type != SQUOTE
			&& data->tokens[i - 1].type != PIPE))
		return (data->exit_code = 2, syntax_error(">"), 1);
	return (0);
}
int	check_syntax_dir(t_data *data, int i)
{
	if (check_syntax_dir2(data, i) == 1)
		return (1);
	else if ((data->tokens[i].type == REDIR_APPEND
			|| data->tokens[i].type == REDIR_HEREDOC
			|| data->tokens[i].type == REDIR_IN
			|| data->tokens[i].type == REDIR_OUT)
		&& i == data->token_count - 1)
		return (data->exit_code = 2, syntax_error("newline"), 1);
	return (0);
}

int check_syntax(t_data *data)
{
	int	i;

	i = data->token_count;
	while (i-- > 0)
	{
		if (data->tokens[i].type == PIPE && i == data->token_count - 1)
			return (data->exit_code = 2, syntax_error("|"), 1);
		else if (data->tokens[i].type == PIPE && i == 0)
			return (data->exit_code = 2, syntax_error("|"), 1);
		else if (data->tokens[i].type == PIPE
			&& (data->tokens[i + 1].type == PIPE
				|| data->tokens[i - 1].type == REDIR_APPEND
				|| data->tokens[i - 1].type == REDIR_HEREDOC
				|| data->tokens[i - 1].type == REDIR_IN
				|| data->tokens[i - 1].type == REDIR_OUT))
			return (data->exit_code = 2, syntax_error("|"), 1);
	}
	i = data->token_count;
	while (i-- > 0)
		if (check_syntax_dir(data, i) == 1)
			return (1);
	return (0);
}

int	lexer(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->input[++i])
	{
		if (data->token_count == data->token_max)
			realloc_tokens(data, data->token_max);
		if (data->input[i] == '|')
			data->tokens[++data->token_count - 1].type = PIPE;
		else if (data->input[i] == '>' || data->input[i] == '<')
			i += fill_redir(data, &data->input[i]) - 1;
		else if (data->input[i] == '\'' || data->input[i] == '\"')
		{
			j = fill_quotes(data, &data->input[i], data->input[i]) - 1;
			if (j < 0)
				return (data->exit_code = 2, syntax_error(&data->input[i]), 1);
			i += j;
		}
		else if (data->input[i] != ' ')
			i += fill_word(data, &data->input[i]) - 1;
		/* else
			continue ;
		printf("token: {%s}\n", data->tokens[data->token_count - 1].value);
		printf("type: %s\n", g_token_type_names[data->tokens[data->token_count
			- 1].type]);
		printf("no_space: %d\n", data->tokens[data->token_count - 1].no_space);
		printf("token_count: %d\n", data->token_count);
		printf("token_max: %d\n", data->token_max);
		printf("--------------------\n"); */
	}
	return (check_syntax(data));
}
