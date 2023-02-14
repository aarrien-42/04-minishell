/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:26:23 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/14 09:22:18 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// export
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

	i = 0;
	ds = (*list);
	ds -> env = ft_strdup(env[i++]);
	ds -> next = NULL;
	while (env[i])
	{
		addlast(env[i], list);
		i++;
	}
}

// env
void	printf_list(t_env **lst)
{
	t_env	*ds;
	int		i;

	ds = *lst;
	i = 0;
	while (ds != NULL)
	{
		printf("%d --> env==|%s|  \n", i, ds->env);
		ds = ds ->next;
		i++;
	}
}

// getenv
int	find_one(char *content, t_env	**list)
{
	t_env	*ds;
	int		i;

	i = 0;
	ds = (*list);
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

// unset
char	*find_var(char *content, t_env	**list)
{
	int		pos;
	char	*string;
	int		i;
	t_env	*ds;

	i = 0;
	ds = (*list);
	pos = find_one(ft_strjoin(content, "="), list);
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

void	eliminate_one(char *content, t_env	**list)
{
	int		pos;
	int		i;
	t_env	*ds;
	t_env	*deleted;
	t_env	*final;

	pos = find_one(content, list);
	i = 1;
	ds = (*list);
	while (ds -> next != NULL && i < pos)
	{
		ds = ds -> next;
		i++;
	}
	deleted = ds -> next;
	final = deleted -> next;
	free(deleted);
	ds ->next = final;
}