/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:41:27 by dgutak            #+#    #+#             */
/*   Updated: 2023/10/30 16:24:30 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	free_tokens(t_token *tokens, int token_max, t_data *data)
{
	while (++token_max < data->token_count)
		ft_free(tokens[token_max].value);
	ft_free(tokens);
	return (1);
}
/* reallocate memory in case there are nott enough space for tokens(multiplies by 2 everytime) */
int	realloc_tokens(t_data *data, int token_max)
{
	t_token	*new_tokens;

	new_tokens = ft_calloc(token_max * 2, sizeof(t_token));
	if (!new_tokens)
		return (print_error(data, "ft_calloc", 1));
	while (--token_max >= 0)
	{
		new_tokens[token_max].type = data->tokens[token_max].type;
		if (data->tokens[token_max].value)
		{
			new_tokens[token_max].value
				= ft_strdup(data->tokens[token_max].value);
			if (!new_tokens[token_max].value)
				return (free_tokens(new_tokens, token_max, data));
		}
		new_tokens[token_max].no_space = data->tokens[token_max].no_space;
		free(data->tokens[token_max].value);
	}
	free(data->tokens);
	data->tokens = new_tokens;
	data->token_max *= 2;
	return (0);
}

/* searches for "PATH=" in env, then splits it by : and store it as alloced 2d array */
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

static char	**split_dup(char **old)
{
	char	**new;
	char	*temp;
	int		i;

	i = ft_len_split(old);
	new = (char **)ft_calloc(sizeof (char *), i + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (old[i] != NULL)
	{
		temp = ft_strdup(old[i]);
		if (temp == NULL)
			return (ft_free_split(new), NULL);
		new[i] = temp;
		i++;
	}
	new[i] = NULL;
	return (new);
}
/* set variables to default values, copy envp, gets path variable */
void	data_init(t_data *data, char **envp)
{
	char	**new_env;

	data->envp = NULL;
	data->path = NULL;
	data->input = NULL;
	data->tokens = NULL;
	data->token_count = 0;
	data->token_max = 1;
	data->exit_code = 0;
	data->cmdt = NULL;
	data->cmdt_count = 0;
	data->pip[0] = 0;
	data->pip[1] = 0;
	data->exit_code = 0;
	new_env = split_dup(envp);
	if (new_env == NULL)
		exit_shell(data, 1);
	data->envp = new_env;
	if (increment_shlvl_variable(data) == FAILURE)
		exit_shell(data, 1); // should be malloc fail, idk the number for sure
	data->path = get_path(data, -1);
}
