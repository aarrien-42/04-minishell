/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:54:57 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/28 10:11:35 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_export(char *content, t_env **anterior)
{
	int		i;
	char	*temp;
	char	*temp2;

	if (!content)
		return (print_env(anterior), 0);
	temp2 = ft_strdup(content);
	i = 0;
	while (content[i])
	{
		if (!ft_strncmp(&content[i], "=", 1))
		{
			temp = ft_strdup_char(content, '=', 1);
			eliminate_one(temp, anterior);
			addlast(temp2, anterior);
			return (free(temp), 0);
		}
		i++;
	}
	temp = ft_strdup_char(content, '=', 1);
	eliminate_one(temp, anterior);
	temp2 = ft_add_char(temp2, '=');
	addlast(temp2, anterior);
	return (free(temp), free(temp2), 0);
}

char	*ft_add_char(char *content, char c)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(content) + 2);
	i = 0;
	while (content[i])
	{
		dest[i] = content[i];
		i++;
	}
	dest[i++] = c;
	dest[i] = '\0';
	free(content);
	return (dest);
}

int	print_env(t_env	**list)
{
	t_env	*ds;
	int		i;

	ds = (*list);
	i = 0;
	ds = ds -> next;
	while (ds -> next != NULL)
	{
		ft_putstr_fd(ds -> env, 1);
		ft_putstr_fd("\n", 1);
		ds = ds -> next;
		i++;
	}
	ft_putstr_fd(ds -> env, 1);
	ft_putstr_fd("\n", 1);
	return (i);
}

int	count_env(t_env	**list)
{
	t_env	*ds;
	int		i;

	ds = (*list);
	i = 0;
	while (ds -> next != NULL)
	{
		ds = ds -> next;
		i++;
	}
	return (i);
}
