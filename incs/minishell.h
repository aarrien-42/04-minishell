/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:57:58 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/14 09:53:36 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../incs/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

/*-STRUCT-*/
typedef struct s_pipex
{
	int			inout_fd[2];
	char		***cmds;
	int			npipes;
	int			**fds;
	char		**env;
}				t_pipex;

typedef struct s_input
{
	int		com;
	int		o_count;
	char	*entrada;
	char	**itxt;
	char	**otxt;
	char	**commd;
	char	**env_var;
	int		**io_pipe;
	t_pipex		*pipex;
}				t_input;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}				t_env;

/*-MAIN-*/
void	print_struckt(t_input	*input);
int		main(int argc, char **argv, char **envp);

/*-FILL__INPUT-*/
int		count_all(t_input *input, char **argv);
void	malloc_all(t_input *input, char **argv);
char	*ft_strdup_char(char *s1, char c, int a);
void	fill_up_input(char	**argv, t_input *input);
int		last_is_char(char *str);

/*-BUILT-*/
void	choose_command(t_input	*input);
void	ft_echo(char **str);
void	ft_cd(char *path);
void	ft_pwd(void);

/*-ENV_LIST-*/
void	addlast(char *content, t_env **anterior);
void	fill_up_env(char **env, t_env	**list);
void	printf_list(t_env **lst);
int		find_one(char *content, t_env	**list);
char	*find_var(char *content, t_env	**list);
void	eliminate_one(char *content, t_env	**list);

/*-INPUT_SPLIT-*/
int		jump_next_block(char *input, int i);
int		count_blocks(char *input);
int		save_word(char *start, char **word);
char	**input_split(char *input, t_env **list);

/*-CLEAN_BLOCK-*/
char	*manage_dollar(char *str, t_env	**list);
int		count_chars(char *block, t_env	**list);
void	create_new_block_loop(char *block, char *new_block, int *i, int *j, t_env	**list);
char	*clean_block(char *block, t_env	**list);

/*-CHANGE_CARACTER-*/
void	change_caracter(t_input *input);

/*-SIGNALS-*/
void	handle_signal(int sig);

/*-ADD_SPACES-*/
char	*add_space(char *entrada, char c);
char	*add_char(char *entrada, char c, int pos);

/*-FT_PIPEX-*/
void	ft_child(t_pipex *gen, int i);
int		ft_fork(t_pipex *gen);
int		count_pipes(char	**str);
void	fill_cmds(t_input	*input);
char	*attach_path(char *cmd);
void	ft_open(t_input	*input);
int		ft_pipex(t_input	*input);

/*-FT_PIPEX_UTILS-*/
void	ft_here_doc(char *limit);
void	ft_error_msg(char *s1, char *s2);
void	ft_close(t_pipex *gen, int n);
void	ft_free_split(char **split);

#endif
