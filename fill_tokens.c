/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:10:22 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/07 14:22:06 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function "len_quotes" calculates the length of a substring within a given string until a
 * specified character is encountered.
 * 
 * @param str A pointer to a character array (string) that contains the input string.
 * @param temp The parameter "temp" is a character that is used as a delimiter. The function
 * "len_quotes" counts the number of characters in the string "str" until it reaches the delimiter
 * character "temp".
 * 
 * @return the length of the substring in the given string `str` before the first occurrence of the
 * character `temp`. If `temp` is not found in `str`, the function returns -1.
 */
static int	len_quotes(char const *str, char temp)
{
	int	len;

	len = 0;
	while (*str && *str != temp)
	{
		len++;
		str++;
	}
	if (*str == 0)
		return (-1);
	return (len);
}

/**
 * The function `len_word` calculates the length of a word in a given string, considering various
 * delimiters.
 * 
 * @param str The parameter `str` is a pointer to a constant character, which means it is a string that
 * cannot be modified.
 * 
 * @return the length of the word in the given string.
 */
static int	len_word(char const *str)
{
	int	len;

	len = 0;
	while (*str && *str != ' ' && *str != '<' && *str != '>' && *str != '|'
		&& *str != '\'' && *str != '\"' && *str != '\t')
	{
		len++;
		str++;
	}
	return (len);
}

/* gets token based on the quotes, namely so 
quoted text is not separated by anything, 
omits quotes in the end result. Sets type and no_space*/
/**
 * The function `fill_quotes` fills a data structure with values from a string, based on a specified
 * delimiter.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param s The parameter `s` is a pointer to a character array (string) that contains the input data.
 * It is used to iterate through the characters in the string.
 * @param temp The parameter `temp` is a character that represents the type of quotes being filled. It
 * can be either `'` (single quote) or `"` (double quote).
 * 
 * @return an integer value.
 */
int	fill_quotes(t_data *data, char const *s, char temp)
{
	int	j;
	int	i;

	j = 0;
	s++;
	i = len_quotes(s, temp);
	if (i == -1)
		return (0);
	data->tokens[++data->token_count - 1].value
		= ft_calloc(i + 1, sizeof(char));
	if (!data->tokens[data->token_count - 1].value)
		return (print_error(data, "ft_calloc", 1) - 2);
	while (*s && *s != temp)
		data->tokens[data->token_count - 1].value[j++] = *s++;
	if (*s++ == '\0')
		return (-1);
	if (*s == '\"' || *s == '\'' || (*s != ' ' && *s != '<' && *s != '>'
			&& *s != '|' && *s != '\0' && *s != '\t'))
		data->tokens[data->token_count - 1].no_space = 1;
	data->tokens[data->token_count - 1].value[j] = '\0';
	if (temp == '\'')
		data->tokens[data->token_count - 1].type = SQUOTE;
	else if (temp == '\"')
		data->tokens[data->token_count - 1].type = DQUOTE;
	return (j + 2);
}

/**
 * The function `fill_word` fills a token with characters from a string until it encounters a
 * delimiter, and assigns the token type as WORD.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param s The parameter `s` is a pointer to a constant character array (string) that represents the
 * input string.
 * 
 * @return the number of characters that were filled into the `value` field of the `tokens` array.
 */
int	fill_word(t_data *data, char const *s)
{
	int	j;

	j = 0;
	data->tokens[++data->token_count - 1].value = ft_calloc(
			len_word(s) + 1, sizeof(char));
	if (!data->tokens[data->token_count - 1].value)
		return (print_error(data, "ft_calloc", 1) - 1);
	while (*s && !(*s == ' ' || *s == '<' || *s == '>' || *s == '|'
			|| *s == '\"' || *s == '\'' || *s == '\t'))
		data->tokens[data->token_count - 1].value[j++] = *s++;
	data->tokens[data->token_count - 1].value[j] = '\0';
	if (*s == '\"' || *s == '\'')
		data->tokens[data->token_count - 1].no_space = 1;
	data->tokens[data->token_count - 1].type = WORD;
	return (j);
}
