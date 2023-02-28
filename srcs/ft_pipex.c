/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:59:42 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/28 10:33:45 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_child(t_pipex *pipex, int i, t_env **list, t_input *input)
{
	int	status;

	status = 0;
	(void)list;
	signal(SIGQUIT, exec_handle_signal);
	if (i != 0)
		dup2(pipex->fds[i - 1][0], STDIN_FILENO);
	if (i != pipex->npipes)
		dup2(pipex->fds[i][1], STDOUT_FILENO);
	ft_close(pipex, pipex->npipes);
	if (choose_command_child(pipex->cmds[i], list) == 0)
	{
		if (pipex->cmds[i])
			status = execve(pipex->cmds[i][0], pipex->cmds[i], pipex->env);
		ft_error_msg("minishell: command not found: ", pipex->cmds[i][0]);
		unlink(".temp.txt");
	}
	ft_free_all(input, *list);
	exit(status);
}

void	ft_fork_loop(t_pipex *pipex, t_env **list, t_input *input, int *i)
{
	int	pid;

	while (pipex->npipes - *i + 1 > 0)
	{
		signal(SIGINT, exec_handle_signal);
		pid = fork();
		if (pid == 0)
			ft_child(pipex, *i, list, input);
		ft_close(pipex, *i);
		waitpid(pid, &g_exit, 0);
		if (WIFEXITED(g_exit))
			g_exit = WEXITSTATUS(g_exit);
		(*i)++;
	}
}

int	ft_fork(t_pipex *pipex, t_env **list, t_input *input)
{
	int	i;
	int	temp1;
	int	temp2;

	i = 0;
	temp1 = dup(STDIN_FILENO);
	temp2 = dup(STDOUT_FILENO);
	dup2(pipex->inout_fd[0], STDIN_FILENO);
	dup2(pipex->inout_fd[1], STDOUT_FILENO);
	if (choose_command_father(pipex->cmds[i], input, list) != 0)
		i++;
	ft_fork_loop(pipex, list, input, &i);
	signal(SIGINT, handle_signal);
	dup2(temp1, STDIN_FILENO);
	dup2(temp2, STDOUT_FILENO);
	return (0);
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
		i = -1;
		while (input->pipex->cmds[j][++i])
			if (i == 0 && input->pipex->cmds[j][i][0] != '/')
				input->pipex->cmds[j][i] = \
					attach_path(input->pipex->cmds[j][i], list);
		j++;
	}
	i = 0;
	input->pipex->fds = malloc(input->pipex->npipes * sizeof(int *));
	while (input->pipex->npipes - i > 0)
	{
		input->pipex->fds[i] = malloc(2 * sizeof(int));
		pipe(input->pipex->fds[i++]);
	}
	ft_open(input);
	ft_fork(input->pipex, list, input);
	return (0);
}
