/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:10:22 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/03 16:08:19 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	len_word(char const *str)
{
	int	len;

	len = 0;
	while (*str && *str != ' ' && *str != '<' && *str != '>' && *str != '|'
		&& *str != '\'' && *str != '\"')
	{
		len++;
		str++;
	}
	return (len);
}

/* gets token based on the quotes, namely so 
quoted text is not separated by anything, 
omits quotes in the end result. Sets type and no_space*/
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
		return (print_error(data, "ft_calloc", 1) - 3);
	while (*s && *s != temp)
		data->tokens[data->token_count - 1].value[j++] = *s++;
	if (*s++ == '\0')
		return (-1);
	if (*s == '\"' || *s == '\'' || (*s != ' ' && *s != '<' && *s != '>'
			&& *s != '|' && *s != '\0'))
		data->tokens[data->token_count - 1].no_space = 1;
	data->tokens[data->token_count - 1].value[j] = '\0';
	if (temp == '\'')
		data->tokens[data->token_count - 1].type = SQUOTE;
	else if (temp == '\"')
		data->tokens[data->token_count - 1].type = DQUOTE;
	return (j + 2);
}

int	fill_word(t_data *data, char const *s)
{
	int	j;

	j = 0;
	data->tokens[++data->token_count - 1].value = ft_calloc(
			len_word(s) + 1, sizeof(char));
	if (!data->tokens[data->token_count - 1].value)
		return (print_error(data, "ft_calloc", 1) - 2);
	while (*s && !(*s == ' ' || *s == '<' || *s == '>' || *s == '|'
			|| *s == '\"' || *s == '\''))
		data->tokens[data->token_count - 1].value[j++] = *s++;
	data->tokens[data->token_count - 1].value[j] = '\0';
	if (*s == '\"' || *s == '\'')
		data->tokens[data->token_count - 1].no_space = 1;
	data->tokens[data->token_count - 1].type = WORD;
	return (j);
}
