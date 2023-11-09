/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:23:45 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/03 18:34:58 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* reset variable to new value */
/**
 * The function "set_variable" sets the value of a given key in the data structure, updating it if it
 * already exists or creating a new variable if it doesn't.
 * 
 * @param data A pointer to a structure of type t_data, which contains information about the program's
 * environment variables.
 * @param key A string representing the key of the variable to be set.
 * @param value The "value" parameter is a string that represents the value to be assigned to the
 * variable identified by the "key" parameter.
 * 
 * @return an integer value. The possible return values are:
 * - `MALLOC_F` if there is a memory allocation error
 * - `SUCCESS` if the variable is successfully set
 * - `create_variable()` if the variable is not found and a new variable is created
 */
int	set_variable(t_data *data, char *key, char *value)
{
	char	*temp;
	char	*new;
	int		i;

	i = get_variable_numb(data->envp, key);
	if (i == -1)
		return (create_variable(data, key, value));
	temp = ft_strcat(key, "=");
	if (temp == NULL)
		return (MALLOC_F);
	new = ft_strcat(temp, value);
	free(temp);
	free(data->envp[i]);
	data->envp[i] = new;
	return (SUCCESS);
}

/* should be useful */
/**
 * The function "starts_with" checks if a given string starts with a specific substring.
 * 
 * @param string A pointer to a character array representing the string to check.
 * @param begin The "begin" parameter is a pointer to a character array that represents the beginning
 * of a string.
 * 
 * @return 1 if the string starts with the specified beginning string, and 0 otherwise.
 */
int	starts_with(char *string, char *begin)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (begin[i] && string[i] && begin[i] == string[i])
		i++;
	return (begin[i] == '\0');
}

/*
envp stands for variables, name in format 'NAME'm without '=' at the end.
is the name of the variable you want to find.
ONLY FOR READING.
IMO useless
*/
/**
 * The function "get_variable" searches for a variable in an array of environment variables and returns
 * the variable if found.
 * 
 * @param envp envp is a pointer to an array of strings, where each string represents an environment
 * variable in the format "name=value". The last element of the array is NULL, indicating the end of
 * the list.
 * @param name The name of the variable you want to find in the environment.
 * 
 * @return a pointer to a character array (string) that matches the given name in the environment
 * variables array. If a match is found, the function returns the entire environment variable string.
 * If no match is found, the function returns NULL.
 */
char	*get_variable(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (starts_with(envp[i], name) && envp[i][ft_strlen(name)] == '=')
			return (envp[i]);
		i++;
	}
	return (NULL);
}

/*
envp stands for variables, name in format 'NAME', without '=' at the end.
is the name of the variable you want to find.
for any purpose.
-1 in case of failure, or positive number in case of success
*/
/**
 * The function "get_variable_numb" searches for a variable in an array of environment variables and
 * returns its index if found, or -1 if not found.
 * 
 * @param envp The `envp` parameter is a pointer to an array of strings, where each string represents
 * an environment variable. Each string is in the format "name=value".
 * @param name The name parameter is a string that represents the name of the variable we are searching
 * for in the envp array.
 * 
 * @return the index of the variable in the `envp` array if it is found, otherwise it is returning -1.
 */
int	get_variable_numb(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (starts_with(envp[i], name) && envp[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/**
 * The function increments the value of the SHLVL environment variable by 1.
 * 
 * @param data A pointer to a struct called "t_data" which contains information about the program's
 * environment variables (envp).
 * 
 * @return either SUCCESS or FAILURE.
 */
int	increment_shlvl_variable(t_data *data)
{
	char	*new_prop;
	char	*new_value;
	int		current;
	int		shlvl;

	shlvl = get_variable_numb(data->envp, "SHLVL");
	if (shlvl == -1)
		return (create_variable(data, "SHLVL", "1"));
	current = ft_atoi(data->envp[shlvl] + 6);
	if (current == 0)
		return (FAILURE);
	new_value = ft_itoa(current + 1);
	if (new_value == NULL)
		return (FAILURE);
	new_prop = ft_strcat("SHLVL=", new_value);
	free(new_value);
	if (new_prop == NULL)
		return (FAILURE);
	free(data->envp[shlvl]);
	data->envp[shlvl] = new_prop;
	return (SUCCESS);
}
