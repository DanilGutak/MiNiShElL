/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:43:19 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/03 19:59:30 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function "get_variable_value" retrieves the value of a variable from a given data structure.
 * 
 * @param data A pointer to a struct called "t_data" which contains various data members including
 * "exit_code" and "envp".
 * @param key A string representing the key of the variable whose value we want to retrieve.
 * 
 * @return a pointer to a character array (string).
 */
char	*get_variable_value(t_data *data, char *key)
{
	int		i;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(data->exit_code));
	i = get_variable_numb(data->envp, key);
	if (i == -1)
		return (NULL);
	return (ft_strdup(data->envp[i] + ft_strlen(key) + 1));
}

/**
 * The function `delete_variable` deletes a variable from an array of strings.
 * 
 * @param data A pointer to a struct of type t_data, which contains information about the environment
 * variables.
 * @param key The key parameter is a string that represents the variable name that you want to delete
 * from the data structure.
 * 
 * @return either SUCCESS or FAILURE.
 */
int	delete_variable(t_data *data, char *key)
{
	char		**new;
	const int	position = get_variable_numb(data->envp, key);
	int			size;
	int			i;

	if (position == -1)
		return (FAILURE);
	size = ft_len_split(data->envp);
	new = (char **)ft_calloc(sizeof (char *), size);
	if (!new)
		return (MALLOC_F);
	i = 0;
	while (i < size)
	{
		new[i] = data->envp[ft_tr(i < position, i, i + 1)];
		i++;
	}
	free(data->envp[position]);
	free(data->envp);
	data->envp = new;
	return (SUCCESS);
}

/**
 * The function checks if a given key is valid, meaning it starts with a letter or underscore and
 * contains only alphanumeric characters or underscores.
 * 
 * @param key A pointer to a character array representing the key that needs to be validated.
 * 
 * @return an integer value. If the key is valid, it returns 1. If the key is not valid (i.e., it is
 * NULL or contains characters other than alphabets, digits, or underscores), it returns 0.
 */
int	is_valid_key(char *key)
{
	if (key == NULL || !(ft_isalpha(*key) || *key == '_'))
		return (0);
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (0);
		key++;
	}
	return (1);
}

/**
 * The function creates a new environment variable by appending a key-value pair to the existing
 * environment variable list.
 * 
 * @param data A pointer to a structure of type t_data, which contains some data including an array of
 * strings called envp.
 * @param key A string representing the key of the variable to be created.
 * @param value The `value` parameter in the `create_variable` function is a string that represents the
 * value to be assigned to the variable.
 * 
 * @return an integer value. The possible return values are:
 * - MALLOC_F: indicating a failure in memory allocation
 * - SUCCESS: indicating a successful creation of the variable
 */
int	create_variable(t_data *data, char *key, char *value)
{
	char	**new;
	char	*buffer;
	char	*new_one;
	int		size;
	int		i;

	buffer = ft_strcat(key, "=");
	if (buffer == NULL)
		return (MALLOC_F);
	new_one = ft_strcat(buffer, value);
	free(buffer);
	if (new_one == NULL)
		return (MALLOC_F);
	size = ft_len_split(data->envp);
	new = (char **)ft_calloc(sizeof (char *), size + 2);
	if (new == NULL)
		return (free(new_one), MALLOC_F);
	i = -1;
	while (++i < size)
		new[i] = data->envp[i];
	new[i++] = new_one;
	new[i] = NULL;
	free(data->envp);
	data->envp = new;
	return (SUCCESS);
}

/**
 * The function appends a value to an existing variable in a data structure.
 * 
 * @param data A pointer to a struct of type t_data, which contains information about the environment
 * variables.
 * @param key A string representing the key of the variable to be appended.
 * @param value The "value" parameter is a string that represents the value to be appended to the
 * existing variable.
 * 
 * @return an integer value. The possible return values are:
 * - `create_variable(data, key, value)`: This is a function call that is returning an integer value.
 * The specific value depends on the implementation of the `create_variable` function.
 * - `MALLOC_F`: This is a constant that represents a specific error code related to memory allocation
 * failure.
 * - `SUCCESS`: This is
 */
int	append_variable(t_data *data, char *key, char *value)
{
	char	*temp;
	int		position;

	position = get_variable_numb(data->envp, key);
	if (position == -1)
		return (create_variable(data, key, value));
	temp = ft_strcat(data->envp[position], value);
	free(temp);
	if (temp == NULL)
		return (MALLOC_F);
	free(data->envp[position]);
	data->envp[position] = temp;
	return (SUCCESS);
}
