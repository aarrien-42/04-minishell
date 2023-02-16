/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:59:42 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/16 17:08:48 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_child(t_pipex *pipex, int i, t_env **list)
{
	(void)list;
	if (i != 0)
		dup2(pipex->fds[i - 1][0], STDIN_FILENO);
	if (i != pipex->npipes)
		dup2(pipex->fds[i][1], STDOUT_FILENO);
	ft_close(pipex, pipex->npipes);
	if (pipex->cmds[i])
		execve(pipex->cmds[i][0], pipex->cmds[i], pipex->env);
	ft_error_msg("pipex: command not found: ", pipex->cmds[i][0]);
	unlink(".temp.txt");
	exit(0);
	exit(0);
}

int	ft_fork(t_pipex *pipex, t_env **list)
{
	int	pid;
	int	i;
	int	temp1;
	int	temp2;

	i = 0;
	temp1 = dup(STDIN_FILENO);
	temp2 = dup(STDOUT_FILENO);
	dup2(pipex->inout_fd[0], STDIN_FILENO);
	dup2(pipex->inout_fd[1], STDOUT_FILENO);
	while (pipex->npipes - i + 1 > 0)
	{
		if (choose_command(pipex->cmds[i], list) == 0)
		{
			pid = fork();
			if (pid == 0)
				ft_child(pipex, i, list);
			ft_close(pipex, i);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
	dup2(temp1, STDIN_FILENO);
	dup2(temp2, STDOUT_FILENO);
	return (0);
}

// in mode 0 counts pipes
// in mode 1 counts the amount of strings that composes a command
int	count_pipes_and_cmds(char	**str, int mode)
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
char	*attach_path(char *cmd)
{
	char	*p_cmd;
	char	*aux;
	char	**splited;
	int		i;

	p_cmd = getenv("PATH");
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
		i++;
	}
	if (splited[i])
		return (free(cmd), ft_free_split(splited), aux);
	else
		free(aux);
	ft_free_split(splited);
	return (cmd);
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
			input->pipex->inout_fd[1] = open(input->otxt[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			input->pipex->inout_fd[1] = open(input->otxt[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
		input->pipex->inout_fd[1] = 1;
}

// allocs the space required for the t_pipex
// prepares the commands to be executed by execve
int	ft_pipex(t_input *input, t_env **list)
{
	int	i;
	int	j;

	input->pipex->npipes = count_pipes_and_cmds(input->commd, 0);
	fill_cmds(input);
	j = 0;
	while (input->pipex->cmds[j])
	{
		i = 0;
		while (input->pipex->cmds[j][i])
		{
			if (i == 0 && input->pipex->cmds[j][i][0] != '/')
				input->pipex->cmds[j][i] = attach_path(input->pipex->cmds[j][i]);
			i++;
		}
		j++;
	}
	i = 0;
	input->pipex->fds = malloc(input->pipex->npipes * sizeof(int *));
	while (input->pipex->npipes - i > 0)
	{
		input->pipex->fds[i] = malloc(2 * sizeof(int));
		pipe(input->pipex->fds[i]);
		i++;
	}
	ft_open(input);
	ft_fork(input->pipex, list);
	unlink(".temp.txt");
	return (0);
}
