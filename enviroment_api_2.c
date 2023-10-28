/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:43:19 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/28 23:11:44 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* += operator for the variables. key in format 'VAL=' */
int	append_variable(char **envp, char *key, char *value)
{
	char	*new;
	int		position;

	position = get_variable_numb(envp, key);
	if (position == -1)
		return (FAILURE);
	new = ft_strcat(envp[position], value);
	if (new == NULL)
		return (FAILURE); // should exit intead of return NULL
	ft_free(envp[position]);
	envp[position] = new;
	return (SUCCESS);
}

/* delete a variable from the envp */
int	delete_variable(char ***envp, char *key)
{
	char	**new;
	char	position;
	int		size;
	int		i;

	position = get_variable_numb(*envp, key);
	if (position == -1)
		return (FAILURE);
	size = 0;
	while ((*envp)[size])
		size++;
	new = (char **)ft_calloc(sizeof (char *), size);
	if (new)
		return (ft_free_split(*envp), FAILURE); // same here
	i = 0;
	while (i < size)
	{
		new[i] = (*envp)[ft_tr(i < position, i, i + 1)];
		i++;
	}
	new[i] = NULL;
	ft_free(*envp);
	*envp = new;
	return (SUCCESS);
}

int	is_valid_key(char *key)
{
	if (key || !(ft_isalpha(*key) || *key == '_'))
		return (0);
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (0);
		key++;
	}
	return (1);
}

/* should add one more variable to the environment */
int	create_variable(char ***envp, char *key, char *value)
{
	char	**new;
	char	*new_one;
	int		size;
	int		i;

	new_one = ft_strcat(key, value);
	if (new_one == NULL)
		return (FAILURE); // should exit intead of return NULL
	size = 0;
	while ((*envp)[size])
		size++;
	new = (char **)ft_calloc(sizeof (char *), size + 2);
	if (new)
		return (ft_free_split(*envp), FAILURE); // same here
	i = 0;
	while (i < size)
	{
		new[i] = (*envp)[i];
		i++;
	}
	new[i++] = new_one;
	new[i] = NULL;
	ft_free(*envp);
	*envp = new;
	return (SUCCESS);
}
