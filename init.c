/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:41:27 by dgutak            #+#    #+#             */
/*   Updated: 2023/11/07 14:26:34 by dgutak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function "free_tokens" frees the memory allocated for an array of tokens and sets the values to
 * NULL.
 * 
 * @param tokens A pointer to an array of t_token structures.
 * @param token_max The variable `token_max` represents the index of the last token in the `tokens`
 * array.
 * @param data The "data" parameter is a pointer to a structure of type "t_data".
 * 
 * @return 1.
 */
int	free_tokens(t_token *tokens, int token_max, t_data *data)
{
	while (++token_max < data->token_count)
	{
		if (tokens[token_max].value)
		{
			free(tokens[token_max].value);
			tokens[token_max].value = NULL;
		}
	}
	free(tokens);
	tokens = NULL;
	return (1);
}

/* reallocate memory in case
there are nott enough space for	tokens(multiplies by 2 everytime) */
/**
 * The function reallocates memory for an array of tokens, doubling its size, and copies the values
 * from the old array to the new one.
 * 
 * @param data A pointer to a struct of type t_data.
 * @param token_max The parameter `token_max` represents the current maximum number of tokens in the
 * `data` structure.
 * 
 * @return an integer value.
 */
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

/* searches for "PATH=" in env, then
splits it by : and store it as alloced 2d array */
/**
 * The function "get_path" retrieves the value of the "PATH" environment variable and splits it into an
 * array of strings using the ":" delimiter.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param i The parameter `i` is an integer that represents the index of the current element in the
 * `data->envp` array. It is used to iterate through the array and find the element that contains the
 * string "PATH=".
 * 
 * @return a pointer to a pointer to a character (char **).
 */
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
		return (NULL);
	ret = ft_split(find, ':');
	if (!ret)
		return (print_error(data, "ft_split", 1), NULL);
	return (ret);
}

/**
 * The function `split_dup` takes a double pointer to a string array, duplicates each string in the
 * array, and returns a new double pointer to the duplicated array.
 * 
 * @param old old is a pointer to a pointer to a character (char **). It represents an array of
 * strings.
 * 
 * @return a pointer to a newly allocated array of strings.
 */
char	**split_dup(char **old)
{
	char	**new;
	int		i;

	new = (char **)ft_calloc(sizeof(char *), ft_len_split(old) + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (old[i] != NULL)
	{
		new[i] = ft_strdup(old[i]);
		if (new[i] == NULL)
			return (free_double_p(new), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

/* set variables to default values, copy envp, gets path variable */
/**
 * The function initializes a data structure and sets its initial values.
 * 
 * @param data A pointer to a structure of type t_data.
 * @param envp The `envp` parameter is a pointer to an array of strings that represents the environment
 * variables. Each string in the array is in the format "variable=value".
 */
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
	data->exit_code = 0;
	data->mode = INTERACTIVE;
	create_original_fds(data);
	new_env = split_dup(envp);
	if (new_env == NULL)
		exit_shell(data, 1);
	data->envp = new_env;
	if (increment_shlvl_variable(data) == FAILURE)
		exit_shell(data, 0);
}
