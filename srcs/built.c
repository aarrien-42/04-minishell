/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:44:43 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/16 17:28:42 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	choose_command(char **cmd, t_env **list)
{
	int	exist;

	exist = 0;
	if (ft_strncmp(cmd[0], "/bin/echo", 100) == 0 && ++exist)
		ft_echo(cmd);
	if (ft_strncmp(cmd[0], "/usr/bin/cd", 100) == 0 && ++exist)
		ft_cd(cmd);
	if (ft_strncmp(cmd[0], "/bin/pwd", 100) == 0 && ++exist)
		ft_pwd(cmd);
	if (ft_strncmp(cmd[0], "export", 100) == 0 && ++exist)
		if (cmd[1])
			addlast(cmd[1], list);
	if (ft_strncmp(cmd[0], "unset", 100) == 0 && ++exist)
		if (cmd[1])
			eliminate_one(cmd[1], list);
	if (ft_strncmp(cmd[0], "/usr/bin/env", 100) == 0 && ++exist)
		print_env(list);
	if (ft_strncmp(cmd[0], "exit", 100) == 0 && ++exist)
		exit(0);
	return (exist);
}
void	ft_echo(char **str)
{
	int	i;
	int	no_n;

	i = 1;
	no_n = 0;
	if (str[i] && ft_strncmp(str[i], "-n", 100) == 0)
	{
		no_n = 1;
		i++;
	}
	while (str[i] && ft_strncmp(str[i], "|", 100) != 0)
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!no_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_cd(char **cmd)
{
	if (access(cmd[1], F_OK) == 0)
		chdir(cmd[1]);
	else
		ft_putstr_fd("cd: no such file or directory\n", 1);
}

void	ft_pwd(char **cmd)
{
	char	*test;

	test = getcwd(NULL, 0);
	if (test == NULL || cmd[1])
		ft_putstr_fd("Error in pwd\n", 1);
	else
	{
		ft_putstr_fd(test, 1);
		write(1, "\n", 1);
	}
}
