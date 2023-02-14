/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:38:09 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/02 10:42:18 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// jumps to the next quote (" or ')
// or advances positions till end of block
int	jump_next_block(char *input, int i)
{
	int		pos;
	char	quote;

	if (input[i] == '\"' || input[i] == '\'')
	{
		pos = 0;
		quote = input[i];
		while (input[i + pos])
		{
			if (pos > 0 && input[i + pos] == quote)
				break ;
			pos++;
		}
		if (input[i + pos] == '\0')
			return (-1);
		i += pos + 1;
	}
	else
		i++;
	return (i);
}

//the function returns 0 if the input is empty and -1 if quotes aren't closed
int	count_blocks(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] && input[i] == ' ')
			i++;
		if (input[i] && input[i] != ' ')
			count++;
		while (input[i] && input[i] != ' ')
		{
			i = jump_next_block(input, i);
			if (i == -1)
				return (-1);
		}
	}
	return (count);
}

int	save_word(char *start, char **word)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (1)
	{
		if ((start[i] == ' ' || start[i] == '\0') && q == 0)
			return (*word = ft_substr(start, 0, i), i);
		else if (start[i] == '\'' || start[i] == '\"')
		{
			if ((q == 2 && start[i] == '\"') || (q == 1 && start[i] == '\''))
				q = 0;
			else if (q == 0 && start[i] == '\"')
				q = 2;
			else if (q == 0 && start[i] == '\'')
				q = 1;
		}
		i++;
	}
	return (0);
}

char	**input_split(char *input, t_env	**list)
{
	char	**split;
	int		blocks;
	int		i;
	int		j;

	i = 0;
	j = 0;
	blocks = count_blocks(input);
	if (blocks == -1)
		return (printf("quotes not closed\n"), NULL);
	split = malloc((blocks + 1) * sizeof(char *));
	while (j < blocks)
	{
		while (input[i] == ' ')
			i++;
		i += save_word(&input[i], &split[j]);
		j++;
	}
	split[blocks] = NULL;
	i = 0;
	while (split[i])
	{
		split[i] = clean_block(split[i], list);
		i++;
	}
	return (split);
}
