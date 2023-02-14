/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:34:22 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/14 09:52:52 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_here_doc(char *limit)
{
	int		fd;
	char	*line;
	size_t	limit_len;

	limit_len = ft_strlen(limit);
	fd = open(".temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, limit, limit_len + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}

void	ft_error_msg(char *s1, char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_close(t_pipex *gen, int n)
{
	int	i;

	i = 0;
	while (n - i > 0)
	{
		close(gen->fds[i][0]);
		close(gen->fds[i][1]);
		i++;
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
