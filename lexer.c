/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:09:06 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/05 15:26:08 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if string is is arrow, searches for the second one,
	then set type accoringl. */
/**
 * The function `fill_redir` determines the type of redirection based on the input character and
 * updates the corresponding token type in the data structure.
 * 
 * @param data A pointer to a struct of type `t_data`.
 * @param s The parameter `s` is a pointer to a character array (string) that represents a command or
 * input.
 * 
 * @return the value of the variable 'ret'.
 */
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

/**
 * The function checks the syntax of redirection tokens in a given data structure.
 * 
 * @param data A pointer to a struct of type `t_data`.
 * @param i The parameter `i` in the `check_syntax_dir` function represents the index of the current
 * token in the `data->tokens` array.
 * 
 * @return an integer value. If any of the conditions in the if-else if statements are true, it will
 * return 1. Otherwise, it will return 0.
 */
int	check_syntax_dir(t_data *data, int i)
{
	if (data->tokens[i].type == REDIR_APPEND
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (syntax_error(data->tokens[i + 1].type, data), 1);
	else if (data->tokens[i].type == REDIR_HEREDOC
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (syntax_error(data->tokens[i + 1].type, data), 1);
	else if (data->tokens[i].type == REDIR_IN
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (syntax_error(data->tokens[i + 1].type, data), 1);
	else if (data->tokens[i].type == REDIR_OUT
		&& (is_not_redir(data->tokens[i + 1].type) == 0))
		return (syntax_error(data->tokens[i + 1].type, data), 1);
	return (0);
}

/**
 * The function "check_syntax" checks the syntax of a given data structure and returns 1 if there is a
 * syntax error, otherwise it returns 0.
 * 
 * @param data A pointer to a struct of type t_data, which contains information about the tokens and
 * their types.
 * 
 * @return an integer value. If any of the conditions in the while loop are met, the function will
 * return 1. Otherwise, it will return 0.
 */
int	check_syntax(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->token_count)
	{
		if (data->tokens[i].type == PIPE && i == data->token_count - 1)
			return (syntax_error(data->tokens[i].type, data), 1);
		else if (data->tokens[i].type == PIPE && i == 0)
			return (syntax_error(data->tokens[i].type, data), 1);
		else if (data->tokens[i].type == PIPE
			&& data->tokens[i + 1].type == PIPE)
			return (syntax_error(data->tokens[i].type, data), 1);
		else if (data->tokens[i].type == PIPE
			&& (is_not_redir(data->tokens[i - 1].type) == 0))
			return (syntax_error(data->tokens[i].type, data), 1);
		else if (is_not_redir(data->tokens[i].type) == 0
			&& i == data->token_count - 1)
			return (syntax_error(0, data), 1);
		else if (check_syntax_dir(data, i) == 1)
			return (1);
	}
	return (0);
}

/**
 * The function `fill_tokens` is responsible for parsing the input string and filling the token array
 * with the appropriate token types.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param i The variable `i` is a pointer to an integer. It is used as an index to iterate through the
 * `data->input` string.
 * @param j The variable `j` is used as a temporary variable within the `fill_tokens` function. It is
 * initialized to a value before the function is called, but its specific value is not provided in the
 * code snippet you provided.
 * 
 * @return an integer value.
 */
int	fill_tokens(t_data *data, int *i, int j)
{
	if (data->token_count == data->token_max)
		if (realloc_tokens(data, data->token_max) == 1)
			return (1);
	if (data->input[*i] == '|')
		data->tokens[++data->token_count - 1].type = PIPE;
	else if (data->input[*i] == '>' || data->input[*i] == '<')
		*i += fill_redir(data, &data->input[*i]) - 1;
	else if (data->input[*i] == '\'' || data->input[*i] == '\"')
	{
		j = fill_quotes(data, &data->input[*i], data->input[*i]) - 1;
		if (j == -2)
			return (1);
		if (j == -1)
			return (syntax_error(data->input[*i], data), 1);
		*i += j;
	}
	else if (data->input[*i] != ' ' && data->input[*i] != '\t')
	{
		j = fill_word(data, &data->input[*i]) - 1;
		if (j == -1)
			return (print_error(data, "ft_calloc", 1));
		*i += j;
	}
	return (0);
}

/* main entry point for lexer(tokeniser). Separates input string
 by spaces,
quotes and special charactersm,allocate memory for tokens.Checks syntax (quotes,
	redirs , pipes)
token has 3 variables: TYPE - which type, VALUE
	- if its not special character the text in it,
NO_SPACE - whether the token is followed by token which can be concatenated.*/
/**
 * The lexer function tokenizes the input data and checks for syntax errors.
 * 
 * @param data The parameter `data` is a pointer to a `t_data` struct.
 * 
 * @return The function `lexer` is returning the result of the function `check_syntax(data)`.
 */
int	lexer(t_data *data)
{
	int	i;

	i = -1;
	data->tokens = ft_calloc(data->token_max, sizeof(t_token));
	if (!data->tokens)
		return (print_error(data, "ft_calloc", 1));
	while (data->input[++i])
		if (fill_tokens(data, &i, 0) == 1)
			return (1);
	return (check_syntax(data));
}
