/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:09:06 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/27 19:24:11 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* if string is is arrow, searches for the second one, then set type accoringl. */
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

int	check_syntax_dir(t_data *data, int i)
{
	if (data->tokens[i].type == REDIR_APPEND
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (data->exit_code = 2, syntax_error(data->tokens[i + 1].type), 1);
	else if (data->tokens[i].type == REDIR_HEREDOC
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (data->exit_code = 2, syntax_error(data->tokens[i + 1].type), 1);
	else if (data->tokens[i].type == REDIR_IN
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (data->exit_code = 2, syntax_error(data->tokens[i + 1].type), 1);
	else if (data->tokens[i].type == REDIR_OUT
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (data->exit_code = 2, syntax_error(data->tokens[i + 1].type), 1);
	return (0);
}

int check_syntax(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->token_count)
	{
		printf("token: {%s} ", data->tokens[i].value);
		printf("type: %s\n", g_token_type_names[data->tokens[i].type]);
		printf("next token: {%s} ", data->tokens[i + 1].value);
		printf("next type: %s\n", g_token_type_names[data->tokens[i + 1].type]);
		if (data->tokens[i].type == PIPE && i == data->token_count - 1)
			return (data->exit_code = 2, syntax_error(data->tokens[i].type), 1);
		else if (data->tokens[i].type == PIPE && i == 0)
			return (data->exit_code = 2, syntax_error(data->tokens[i].type), 1);
		else if (data->tokens[i].type == PIPE
			&& data->tokens[i + 1].type == PIPE)
			return (data->exit_code = 2, syntax_error(data->tokens[i].type), 1);
		else if (is_not_redir(data->tokens[i].type) == 0
			&& i == data->token_count - 1)
			return (data->exit_code = 2, syntax_error(0), 1);
		else if (check_syntax_dir(data, i) == 1)
			return (1);
	}
	return (0);
}
/* main entry point for lexer(tokeniser). Separates input string
 by spaces,
quotes and special charactersm,allocate memory for tokens.Checks syntax (quotes, redirs , pipes)
token has 3 variables: TYPE - which type, VALUE - if its not special character the text in it,
NO_SPACE - whether the token is followed by token which can be concatenated.*/
int	lexer(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->tokens = ft_calloc(data->token_max, sizeof(t_token));
	if (!data->tokens)
		exit_shell(data, 1);
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
				return (data->exit_code = 2, syntax_error(data->input[i]), 1);
			i += j;
		}
		else if (data->input[i] != ' ')
			i += fill_word(data, &data->input[i]) - 1;
		else
			continue ;
		/* printf("token: {%s}\n", data->tokens[data->token_count - 1].value);
		printf("type: %s\n", g_token_type_names[data->tokens[data->token_count
			- 1].type]);
		printf("no_space: %d\n", data->tokens[data->token_count - 1].no_space);
		printf("token_count: %d\n", data->token_count);
		printf("token_max: %d\n", data->token_max);
		printf("--------------------\n"); */
	}
	return (check_syntax(data));
}
