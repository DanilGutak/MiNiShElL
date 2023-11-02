/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:23:45 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/02 16:34:18 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* reset variable to new value */
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

/* do you really need the description here??? */
int	increment_shlvl_variable(t_data *data)
{
	char	*new_prop;
	char	*new_value;
	int		current;
	int		shlvl;

	shlvl = get_variable_numb(data->envp, "SHLVL");
	if (shlvl == -1)
		return (FAILURE);
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
	data->envp[shlvl] = new_prop;
	return (SUCCESS);
}
