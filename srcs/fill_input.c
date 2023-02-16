/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:45:33 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/14 11:27:43 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	count_all(t_input *input, char **argv)
{
	int	i;
	int	count_signal;
	int	count_block;

	i = 0;
	count_block = 0;
	count_signal = 0;
	while (argv[count_block])
		count_block++;
	while (input -> entrada[i])
	{
		if (ft_strncmp(&input -> entrada[i], ">", 1) == 0
			|| ft_strncmp(&input -> entrada[i], "<", 1) == 0)
		{
			if (ft_strncmp(&input -> entrada[i], ">>", 2) == 0
				|| ft_strncmp(&input -> entrada[i], "<<", 2) == 0)
					i++;
			count_signal = count_signal + 2;
		}
		i++;
	}
	return (count_block - count_signal);
}

void	malloc_all(t_input *input, char **argv)
{
	int	amount_all;
	int	i;

	i = 0;
	amount_all = count_all(input, argv);
	input -> commd = malloc(sizeof(char *) * (amount_all + 1));
	input -> itxt = malloc(sizeof(char *) * (2 + 1));
	input -> otxt = malloc(sizeof(char *) * (2 + 1));
	input -> itxt[0] = NULL;
	input -> otxt[0] = NULL;
	input -> itxt[1] = NULL;
	input -> otxt[1] = NULL;
	input -> itxt[2] = NULL;
	input -> otxt[2] = NULL;
	input -> commd[amount_all] = NULL;
}

char	*ft_strdup_char(char *s1, char c, int a)
{
	char			*p;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (s1[j] && ((a && s1[j] != c) || (!a && s1[j] == c)))
		j++;
	p = malloc(j + 1);
	if (p == 0)
		return (NULL);
	i = 0;
	while (s1[i] && ((a && s1[i] != c) || (!a && s1[i] == c)))
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	fill_up_input(char	**argv, t_input *input)
{
	int		i;

	i = 0;
	input -> com = 0;
	malloc_all(input, argv);
	while (argv[i])
	{
		if (argv[i] && argv[i][0] == '<')
		{
			input->itxt[0] = ft_strdup(argv[i++]);
			input->itxt[1] = ft_strdup(argv[i]);
			if (argv[i])
				i++;
		}
		else if (argv[i] && argv[i][0] == '>')
		{
			input->otxt[0] = ft_strdup(argv[i++]);
			input->otxt[1] = ft_strdup(argv[i]);
			if (argv[i])
				i++;
		}
		else if (argv[i] != NULL)
			input->commd[input -> com++] = ft_strdup(argv[i++]);
	}
}

int	last_is_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (1);
	return (0);
}
