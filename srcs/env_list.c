/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:26:23 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/28 10:16:06 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	addlast(char *content, t_env **anterior)
{
	t_env	*siguiente;
	t_env	*ds;

	siguiente = (t_env *)malloc(sizeof(t_env));
	siguiente -> env = ft_strdup(content);
	siguiente -> next = NULL;
	ds = (*anterior);
	while (ds -> next != NULL)
	{
		ds = ds -> next;
	}
	ds -> next = siguiente;
}

void	fill_up_env(char **env, t_env	**list)
{
	int		i;
	t_env	*ds;
	char	*temp;

	i = 0;
	ds = (*list);
	ds -> env = ft_strdup("ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ");
	ds -> next = NULL;
	while (env[i])
	{
		temp = ft_strdup(env[i]);
		addlast(temp, list);
		free(temp);
		i++;
	}
}

int	find_one(char *content, t_env	**list)
{
	t_env	*ds;
	int		i;

	i = 0;
	ds = (*list);
	if (ds -> next != NULL)
	{
		ds = ds -> next;
		i++;
	}
	while (ds -> next != NULL
		&& ft_strncmp(ds -> env, content, ft_strlen(content)))
	{
		ds = ds -> next;
		i++;
	}
	if (ft_strncmp(ds -> env, content, ft_strlen(content)))
		return (-1);
	return (i);
}

char	*find_var(char *content, t_env	**list)
{
	int		pos;
	char	*string;
	int		i;
	t_env	*ds;
	char	*temp;

	i = 0;
	ds = (*list);
	temp = ft_strjoin(content, "=");
	pos = find_one(temp, list);
	free(temp);
	if (pos == -1)
		return (NULL);
	while (ds -> next != NULL && i < pos)
	{
		ds = ds -> next;
		i++;
	}
	string = ds -> env;
	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	return (&string[i + 1]);
}

t_env	**eliminate_one(char *content, t_env	**list)
{
	int		pos;
	int		i;
	t_env	*ds;
	t_env	*deleted;
	t_env	*final;

	pos = find_one(content, list);
	i = 1;
	ds = (*list);
	if (pos == 0)
		return (list = &(ds->next), free(ds->env), free(ds), list);
	while (ds -> next != NULL && i < pos)
	{
		ds = ds -> next;
		i++;
	}
	deleted = ds -> next;
	final = deleted -> next;
	free(deleted -> env);
	free(deleted);
	ds ->next = final;
	return (list);
}
