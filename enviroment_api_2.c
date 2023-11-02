/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_api_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 21:43:19 by vfrants           #+#    #+#             */
/*   Updated: 2023/11/02 16:05:56 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* delete a variable from the envp */
int	delete_variable(t_data *data, char *key)
{
	char	**new;
	char	position;
	int		size;
	int		i;

	position = get_variable_numb(data->envp, key);
	if (position == -1)
		return (FAILURE);
	size = ft_len_split(data->envp);
	new = (char **)ft_calloc(sizeof (char *), size);
	if (!new)
		return (MALLOC_F); // same error here related to malloc
	i = 0;
	while (i < size)
	{
		new[i] = data->envp[ft_tr(i < position, i, i + 1)];
		i++;
	}
	free(data->envp);
	data->envp = new;
	return (SUCCESS);
}

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

/* should add one more variable to the environment.
 kinda confused about the time when you print errors */
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

/* += operator for the variables. key in format 'VAL'. IDK IF WE NEED IT*/
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
