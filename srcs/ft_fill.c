/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:25:04 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/22 10:26:48 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

// in mode 0 counts pipes
// in mode 1 counts the amount of strings that composes a command
int	count_pipes_and_cmds(char **str, int mode)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	if (mode == 0)
	{
		i = -1;
		while (str[++i])
		{
			j = 0;
			while (str[i][j])
				if (str[i][j++] == '|')
					count++;
		}
	}
	else if (mode == 1)
	{
		i = 0;
		while (str[i] && *str[i] != '|')
			i++;
		count = i;
	}
	return (count);
}

// fills char ***cmds from t_pipex structure
// reads from input->>commd and splits the commands
// separated by a pipe '|'
void	fill_cmds(t_input	*input)
{
	int	i;
	int	j;
	int	amount;
	int	cmd_pos;

	i = 0;
	j = 0;
	amount = 0;
	cmd_pos = 0;
	input->pipex->cmds = malloc((input->pipex->npipes + 2) * sizeof(char **));
	input->pipex->cmds[input->pipex->npipes + 1] = NULL;
	input->pipex->cmds[0] = NULL;
	while (input->commd[i])
	{
		if (*input->commd[i] == '|' && i++)
			cmd_pos++;
		amount = count_pipes_and_cmds(&input->commd[i], 1);
		input->pipex->cmds[cmd_pos] = malloc((amount + 1) * sizeof(char *));
		input->pipex->cmds[cmd_pos][amount] = NULL;
		j = 0;
		while (amount-- > 0)
			input->pipex->cmds[cmd_pos][j++] = ft_strdup(input->commd[i++]);
		if (input->commd[i] && *input->commd[i] != '|')
			i++;
	}
}

// joins the command with its absolute path
// if he doesn't find it does nothing
char	*attach_path(char *cmd, t_env **list)
{
	char	*p_cmd;
	char	*aux;
	char	**splited;
	int		i;

	p_cmd = find_var("PATH", list);
	if (!p_cmd)
		return (cmd);
	splited = ft_split(p_cmd, ':');
	i = 0;
	while (splited[i])
	{
		aux = splited[i];
		splited[i] = ft_strjoin(aux, "/");
		free(aux);
		aux = ft_strjoin(splited[i], cmd);
		if (access(aux, F_OK | X_OK) == 0)
			break ;
		free(aux);
		i++;
	}
	if (splited[i])
		return (free(cmd), ft_free_split(splited), aux);
	return (ft_free_split(splited), cmd);
}

// opens in and out files and saves them fd in the struct
// .temp is created so it needs to be deleted after execution
// if they don't exist
// inout[0] = 1 y inout[1] = 0
void	ft_open(t_input	*input)
{
	if (input->itxt[1])
	{
		if (ft_strlen(input->itxt[0]) == 2)
		{
			ft_here_doc(input->itxt[1]);
			input->pipex->inout_fd[0] = open(".temp.txt", O_RDONLY);
		}
		else
			input->pipex->inout_fd[0] = open(input->itxt[1], O_RDONLY);
	}
	else
		input->pipex->inout_fd[0] = 0;
	if (input->otxt[1])
	{
		if (ft_strlen(input->otxt[0]) == 2)
			input->pipex->inout_fd[1] = open(input->otxt[1],
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			input->pipex->inout_fd[1] = open(input->otxt[1],
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
		input->pipex->inout_fd[1] = 1;
}
