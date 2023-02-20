/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:23:01 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/20 12:05:54 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// searches for the env var and returns it
// if it doesn't exist it returns null
// $? returns the exit state of the last command run
char	*manage_dollar(char *str, t_env	**list, char *end)
{
	int		i;
	char	*env_var;
	char	*var;

	i = 0;
	if (str[i + 1] && str[i + 1] == '?')
		return (ft_itoa(errno));
	while (str[i])
	{
		if (ft_strchr(end, str[i]) != 0 || \
			(str[i] == '$' && i != 0))
			break ;
		i++;
	}
	env_var = ft_substr(str, 1, i - 1);
	var = find_var(env_var, list);
	if (i == 1)
		var = "$";
	free(env_var);
	return (var);
}

// returns the final length of the block to be cleaned
// excluding quotes that aren't gonna print and
// including extra length from env vars (unless is surrounded by ')
int	count_chars(char *block, t_env	**list, char *end)
{
	int		i;
	int		count;
	char	quote;
	char	*env_var;

	i = 0;
	count = 0;
	quote = 0;
	while (block[i])
	{
		if (quote == 0 && (block[i] == '\'' || block[i] == '\"'))
			quote = block[i];
		else if (quote != 0 && block[i] == quote)
			quote = 0;
		else if (quote != '\'' && block[i] == '$')
		{
			env_var = manage_dollar(&block[i], list, end);
			if (env_var)
				count += ft_strlen(env_var);
			while (block[i + 1] && ft_strchr(end, block[i + 1]) == 0 && block[i + 1] != '$')
				i++;
		}
		else if (block[i] != quote || \
			(quote == 0 && block[i] != '\'' && block[i] != '\"'))
			count++;
		i++;
	}
	return (count);
}

void	create_new_block_loop(char *block, char *new_block, int *i, int *j, t_env	**list)
{
	char		*env_var;
	static char	quote;
	char	*end;

	end = " \"\'^.*+?()[]{}|?¿!¡";
	if (quote == 0 && (block[*i] == '\'' || block[*i] == '\"'))
		quote = block[(*i)++];
	while (block[*i] == '$' && quote != '\'')
	{
		env_var = manage_dollar(&block[*i], list, end);
		while (env_var && *env_var)
			new_block[(*j)++] = *env_var++;
		(*i)++;
		while (block[*i] && block[*i] != '$' && ft_strchr(end, block[*i]) == 0)
			(*i)++;
	}
	if (quote == 0 && (block[*i] == '\'' || block[*i] == '\"'))
		quote = block[(*i)++];
	else if (block[*i] && ((block[*i] != quote)
			|| (block[*i] == '$' && quote == '\'')))
		if (block[*i] != quote)
			new_block[(*j)++] = block[(*i)++];
	if (quote != 0 && block[*i] == quote && (*i)++)
		quote = 0;
}

// quotes that are not gonna be printed are removed
// if not surrounded by simple quotes(') env variables are shown
char	*clean_block(char *block, t_env	**list, char *end)
{
	char	*new_block;
	int		chars;
	int		j;
	int		i;

	i = 0;
	j = 0;
	chars = count_chars(block, list, end);
	if (chars == 0)
		return (NULL);
	new_block = malloc((chars + 1) * sizeof(char));
	while (block[i])
		create_new_block_loop(block, new_block, &i, &j, list);
	new_block[chars] = '\0';
	return (new_block);
}
