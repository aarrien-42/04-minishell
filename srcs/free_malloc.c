/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:19:56 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/27 13:36:23 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_all(t_input	*input, t_env *list)
{
	int	i;
	int	j;

	j = 0;
	while (input->pipex->cmds && input->pipex->cmds[j])
	{
		i = 0;
		while (input->pipex->cmds[j][i])
		{
			free(input->pipex->cmds[j][i]);
			i++;
		}
		free(input->pipex->cmds[j]);
		j++;
	}
	if (input->entrada)
		free(input->entrada);
	free_doble_string(input->itxt);
	free_doble_string(input->otxt);
	free_doble_string(input->commd);
	free_doble_int(input->pipex->fds, input);
	free_list(&list);
	unlink(".temp.txt");
}

void	ft_free(t_input	*input, char **argv)
{
	int	i;
	int	j;

	j = 0;
	while (input->pipex->cmds && input->pipex->cmds[j])
	{
		i = 0;
		while (input->pipex->cmds[j][i])
		{
			free(input->pipex->cmds[j][i]);
			i++;
		}
		free(input->pipex->cmds[j]);
		j++;
	}
	free(input->pipex->cmds);
	if (input->entrada)
		free(input->entrada);
	free_doble_string(input->itxt);
	free_doble_string(input->otxt);
	free_doble_string(input->commd);
	free_doble_string(argv);
	free_doble_int(input->pipex->fds, input);
	unlink(".temp.txt");
}

void	free_doble_string(char **string)
{
	int	i;

	i = 0;
	if (string)
	{
		while (string[i] != NULL)
			free(string[i++]);
		free(string);
	}
}

void	free_doble_int(int **string, t_input *input)
{
	int	i;

	i = 0;
	if (string)
	{
		while (i < input->pipex->npipes)
			free(string[i++]);
		free(string);
	}
}

void	free_list(t_env **list_a)
{
	t_env	*ds;
	int		i;

	i = count_env(list_a);
	ds = (*list_a);
	while (i > 0)
	{
		(*list_a) = (*list_a)-> next;
		free(ds->env);
		free(ds);
		ds = (*list_a);
		i--;
	}
	free(ds->env);
	free(ds);
}
