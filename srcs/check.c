/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:51:33 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/14 11:27:59 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// checks for pipes so they are not at the start
// at the end or one after the other
int	check_pipe(char *input, int i)
{
	int	c_i;

	c_i = i;
	while (1)
	{
		if (i < 0)
			return (1);
		if (input[i] != ' ' && input[i] != '|')
			break ;
		i--;
	}
	i = c_i;
	while (input[i++])
	{
		if (input[i] == '|')
			return (1);
		if (input[i] && input[i] != '|' && input[i] != ' ')
			return (0);
	}
	return (1);
}

// checks if there's anything to the right of
// '<' or '>' and redirects in case of '|'
int	check_right(char *input, int i, char c)
{
	char	o;

	o = c + 2 - (c % 60 * 2);
	if (c == '<' || c == '>')
	{
		while (input[i] && input[i] != o)
		{
			if (input[i] != c && input[i] != ' ')
				return (0);
			i++;
		}
	}
	else
		if (check_pipe(input, i) == 0)
			return (0);
	return (1);
}

int	check_input_loop(char *input, int *i, int *re_l, int *re_r)
{
	if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
		if (check_right(input, *i, input[*i]) == 1)
			return (1);
	if (*re_l == 0 && input[*i] == '<')
		while (input[*i] == '<' && input[(*i)++])
			(*re_l)++;
	else if (*re_r == 0 && input[*i] == '>')
		while (input[*i] == '>' && input[(*i)++])
			(*re_r)++;
	else if (input[*i] == '>' || input[*i] == '<')
		return (1);
	return (0);
}

int	check_input(char *input)
{
	int		i;
	char	quote;
	int		re_l;
	int		re_r;

	i = -1;
	quote = 0;
	re_l = 0;
	re_r = 0;
	while (i < (int)ft_strlen(input) && input[++i])
	{
		if (quote == 0 && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote != 0 && input[i] == quote)
			quote = 0;
		if (quote != 0)
			continue ;
		if (check_input_loop(input, &i, &re_l, &re_r) == 1)
			return (1);
	}
	if (quote != 0 || re_l > 2 || re_r > 2)
		return (1);
	return (0);
}
