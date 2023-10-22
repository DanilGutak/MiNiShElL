/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:09:06 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/22 13:37:00 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_word(char const *str, int in_quotes)
{
	int	len;
	int	temp;

	len = 0;
	temp = 0;
	while (*str && !((*str == ' ' || *str == '<' || *str == '>' || *str == '|')
			&& !in_quotes))
	{
		if ((*str == '\"' || *str == '\'') && !in_quotes && !temp)
			break ;
		if ((*str == '\"' || *str == '\'') && !in_quotes)
		{
			in_quotes = 1;
			temp = *str;
		}
		else if (*str == temp)
			in_quotes = 0;
		len++;
		str++;
	}
	return (len);
}

int	fill_word(t_data *data, char const *s)
{
	int		in_quotes;
	char	temp;
	int		j;

	in_quotes = 0;
	j = 0;
	temp = 0;
	data->tokens[++data->token_count - 1].value = malloc(sizeof(char)
			* (len_word(s, 0) + 1));
	if (!data->tokens[data->token_count - 1].value)
		exit_shell(data, 1, NULL);
	while (*s && !((*s == ' ' || *s == '<' || *s == '>' || *s == '|')
			&& !in_quotes))
	{
		if ((*s == '\"' || *s == '\'') && !in_quotes && ++in_quotes)
			temp = *s++;
		else if (*s == temp && s++)
			in_quotes = 0;
		else
			data->tokens[data->token_count - 1].value[j++] = *s++;
	}
	if (*s == '\"' || *s == '\'')
		data->tokens[data->token_count - 1].no_space = 1;
	data->tokens[data->token_count - 1].value[j] = '\0';
	if (in_quotes == 1)
		exit_shell(data, 2, &temp);
	return (j);
}

void	lexer(t_data *data)
{
	int	i;

	i = -1;
	while (data->input[++i])
	{
		if (data->input[i] == '|')
			continue ;
		else if (data->input[i] == '>')
			continue ;
		else if (data->input[i] == '<')
			continue ;
		else if (data->input[i] == '\'' || data->input[i] == '\"')
		{
			i += fill_word(data, &data->input[i]) - 1;
			printf("input: %s\n", data->tokens[data->token_count - 1].value);
		}
		else if (data->input[i] == ' ')
			continue ;
		else
		{
			i += fill_word(data, &data->input[i]) - 1;
			printf("input: %s\n", data->tokens[data->token_count - 1].value);
		}
	}
}
