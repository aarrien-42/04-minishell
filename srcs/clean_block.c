/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:23:01 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/21 12:17:56 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// searches for the env var and returns it
// if it doesn't exist it returns null
// $? returns the exit state of the last command run
char	*manage_dollar(char *str, t_env	**list, char *end, int *x)
{
	int		i;
	char	*env_var;
	char	*var;

	i = 0;
	if (str[i + 1] && str[i + 1] == '?')
		return ((*x)++, ft_itoa(g_exit));
	if (str[i + 1] && str[i + 1] == '$')
		return ((*x)++, "55082");
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

// returns the final length of the b to be cleaned
// excluding quotes that aren't gonna print and
// including extra length from env vars (unless is surrounded by ')
int	count_chars(char *b, t_env	**list, char *end, int i)
{
	int		count;
	char	quote;
	char	*env_var;

	count = 0;
	quote = 0;
	while (b[++i])
	{
		if (quote == 0 && (b[i] == '\'' || b[i] == '\"'))
			quote = b[i];
		else if (quote != 0 && b[i] == quote)
			quote = 0;
		else if (quote != '\'' && b[i] == '$')
		{
			env_var = manage_dollar(&b[i], list, end, &i);
			if (env_var)
				count += ft_strlen(env_var);
			while (b[i + 1] && ft_strchr(end, b[i + 1]) == 0 && b[i + 1] != '$')
				i++;
		}
		else if (b[i] != quote || \
			(quote == 0 && b[i] != '\'' && b[i] != '\"'))
			count++;
	}
	return (count);
}

void	create_new_block_loop(char **n_b, int *i, int *j, t_env	**list)
{
	char		*env_var;
	static char	quote;
	char		*end;

	end = " \"\'^.*+()[]{}|¿!¡";
	if (quote == 0 && (n_b[0][*i] == '\'' || n_b[0][*i] == '\"'))
		quote = n_b[0][(*i)++];
	while (n_b[0][*i] == '$' && quote != '\'')
	{
		env_var = manage_dollar(&n_b[0][*i], list, end, i);
		while (env_var && *env_var)
			n_b[1][(*j)++] = *env_var++;
		(*i)++;
		while (n_b[0][*i] && n_b[0][*i] != '$'
			&& ft_strchr(end, n_b[0][*i]) == 0)
			(*i)++;
	}
	if (quote == 0 && (n_b[0][*i] == '\'' || n_b[0][*i] == '\"'))
		quote = n_b[0][(*i)++];
	else if (n_b[0][*i] && ((n_b[0][*i] != quote)
			|| (n_b[0][*i] == '$' && quote == '\'')))
		if (n_b[0][*i] != quote)
			n_b[1][(*j)++] = n_b[0][(*i)++];
	if (quote != 0 && n_b[0][*i] == quote && (*i)++)
		quote = 0;
}

// quotes that are not gonna be printed are removed
// if not surrounded by simple quotes(') env variables are shown
char	*clean_block(char *block, t_env	**list, char *end)
{
	char	*new_b;
	int		chars;
	char	**n_b;
	int		i;
	int		j;

	i = 0;
	j = 0;
	chars = count_chars(block, list, end, -1);
	if (chars == 0)
		return (NULL);
	new_b = malloc((chars + 1) * sizeof(char));
	n_b = malloc(2 * sizeof(char *));
	n_b[0] = block;
	n_b[1] = new_b;
	while (block[i])
		create_new_block_loop(n_b, &i, &j, list);
	free(n_b);
	new_b[chars] = '\0';
	free(block);
	return (new_b);
}
