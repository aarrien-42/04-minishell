/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:44:43 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/14 09:46:38 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	choose_command(t_input	*input)
{
	if (ft_strncmp(input->commd[0], "echo", 100) == 0)
		ft_echo(&input->commd[1]);
	if (ft_strncmp(input->commd[0], "cd", 100) == 0)
		ft_cd(input->commd[1]);
	if (ft_strncmp(input->commd[0], "pwd", 100) == 0)
		ft_pwd();
}

void	ft_echo(char **str)
{
	int	i;
	int	j;
	int	no_n;

	i = 0;
	no_n = 0;
	j = 1;
	if (str[i] && ft_strncmp(str[i], "-n", 100) == 0)
	{
		no_n = 1;
		i++;
	}
	while (str[i] && ft_strncmp(str[i], "|", 100) != 0)
	{
		ft_putstr_fd(str[i], 0);
		ft_putstr_fd(" ", 0);
		i++;
	}
	if (!no_n)
		ft_putstr_fd("\n", 0);
}

void	ft_cd(char *path)
{
	if (!access(path, 0) && path[0] == '/')
	{
		while (chdir("..") > 0)
			;
		chdir(path);
	}
	else if (chdir(path) < 0)
		ft_putstr_fd("cd: no such file or directory\n", 1);

}

void	ft_pwd(void)
{
	char	*test;

	test = getcwd(NULL, 0);
	if (test == NULL)
		ft_putstr_fd("Error in pwd\n", 1);
	else
	{
		ft_putstr_fd(test, 1);
		write(1, "\n", 1);
	}
}
