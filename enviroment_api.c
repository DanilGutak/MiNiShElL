/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:23:45 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/28 21:44:47 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* should be useful */
int	starts_with(char *string, char *begin)
{
	while (*string)
	{
		if (!*begin || *string != *begin)
			return (0);
		begin++;
		string++;
	}
	return (1);
}

/*
envp stands for variables, name in format 'VAR='
is the name of the variable you want to find.
ONLY FOR READING
IMO useless
*/
char	*get_variable(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (starts_with(envp[i], name))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

/*
envp stands for variables, name in format 'VAR='
is the name of the variable you want to find
for any purpose.
-1 in case of failure, or positive number in case of success
*/
int	get_variable_numb(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (starts_with(envp[i], name))
			return (i);
		i++;
	}
	return (-1);
}

/* do you really need the description here??? */
int	increment_shlvl_variable(char **envp)
{
	char	*new_prop;
	char	*new_value;
	int		current;
	int		shlvl;

	shlvl = get_variable_numb(envp, "SHLVL=");
	if (shlvl == -1)
		return (FAILURE);
	current = ft_atoi(envp[shlvl] + 6);
	if (current == 0)
		return (FAILURE);
	new_value = ft_itoa(++current);
	if (new_value == NULL)
		return (FAILURE);
	new_prop = ft_strcat("SHLVL=", new_value);
	if (new_prop == NULL)
		return (ft_free(new_value), FAILURE);
	envp[shlvl] = new_prop;
	return (SUCCESS);
}
