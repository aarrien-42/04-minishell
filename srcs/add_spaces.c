/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:31:24 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/23 10:25:21 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*add_space(char *entrada, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (entrada[i] && i < 100)
	{
		if (quote == 0
			&& (entrada[i] == '\'' || entrada[i] == '\"'))
				quote = entrada[i];
		else if (quote != 0 && entrada[i] == quote)
			quote = 0;
		if (quote == 0 && entrada[i] == c)
		{
			if (i > 0 && entrada[i - 1] != c)
			{
				entrada = add_char(entrada, ' ', i - 1);
				i++;
			}
			if (entrada[i + 1] && entrada[i + 1] != c)
				entrada = add_char(entrada, ' ', i++);
		}
		i++;
	}
	return (entrada);
}

char	*add_char(char *entrada, char c, int pos)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(entrada);
	new_str = malloc(len + 2);
	i = 0;
	j = 0;
	while (entrada[i])
	{
		if (pos + 1 == i)
			new_str[j++] = c;
		new_str[j++] = entrada[i];
		i++;
	}
	new_str[j] = entrada[i];
	free(entrada);
	return (new_str);
}
