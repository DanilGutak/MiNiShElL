/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:41:27 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/24 21:39:15 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens, int token_max, t_data *data)
{
	while (++token_max < data->token_count)
		if (tokens[token_max].value)
			free(tokens[token_max].value);
	free(tokens);
	exit_shell(data, 1);
}

void	realloc_tokens(t_data *data, int token_max)
{
	t_token	*new_tokens;

	new_tokens = ft_calloc(token_max * 2, sizeof(t_token));
	if (!new_tokens)
		exit_shell(data, 1);
	while (--token_max >= 0)
	{
		new_tokens[token_max].type = data->tokens[token_max].type;
		if (data->tokens[token_max].value)
		{
			new_tokens[token_max].value
				= ft_strdup(data->tokens[token_max].value);
			if (!new_tokens[token_max].value)
				free_tokens(new_tokens, token_max, data);
		}
		new_tokens[token_max].no_space = data->tokens[token_max].no_space;
		free(data->tokens[token_max].value);
	}
	free(data->tokens);
	data->tokens = new_tokens;
	data->token_max *= 2;
}

char	**get_path(t_data *data, int i)
{
	char	**ret;
	char	*find;

	while (data->envp[++i])
	{
		find = ft_strstr(data->envp[i], "PATH=");
		if (find != NULL)
			break ;
	}
	if (data->envp[i] == NULL)
		exit_shell(data, 1);
	ret = ft_split(find, ':');
	if (!ret)
		exit_shell(data, 1);
	i = -1;
	while (ret[++i])
	{
		ret[i] = ft_strjoin(ret[i], "/");
		if (!ret[i])
		{
			free_double_p(ret);
			exit_shell(data, 1);
		}
	}
	return (ret);
}

void	data_init(t_data *data, char **envp)
{
	data->envp = envp;
	data->path = NULL;
	data->input = NULL;
	data->token_max = 1;
	data->token_count = 0;
	data->exit_code = 0;
	data->cmdt = NULL;
	data->cmdt_count = 0;
	data->path = get_path(data, -1);
}
