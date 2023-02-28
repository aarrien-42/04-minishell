/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:31:08 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/28 10:05:52 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init(t_input **input, t_env **list, char **env)
{
	(*list) = (t_env *)malloc(sizeof(t_env));
	(*input) = malloc(sizeof(t_input));
	(*input)->pipex = malloc(sizeof(t_pipex));
	(*input)->pipex->env = env;
	fill_up_env(env, list);
}

void	program(t_input **input, t_env **list, char **argv)
{
	change_caracter((*input));
	(*input)->entrada = add_space((*input)->entrada, '|');
	(*input)->entrada = add_space((*input)->entrada, '<');
	(*input)->entrada = add_space((*input)->entrada, '>');
	argv = input_split((*input)->entrada, list);
	fill_up_input(argv, (*input));
	ft_pipex((*input), list);
	ft_free((*input), argv);
}

int	main(int ac, char **av, char **env)
{
	t_input	*input;
	char	**argv;
	t_env	*list;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	argv = NULL;
	init(&input, &list, env);
	while (1)
	{
		input->entrada = readline("minishell> ");
		if (input->entrada == NULL)
			exit(0);
		if (check_input(input->entrada) != 0)
		{
			printf("INPUT ERROR\n");
			continue ;
		}
		if (*input->entrada != 0)
			add_history (input->entrada);
		else
			continue ;
		program(&input, &list, argv);
	}
	return ((void)ac, (void)av, ft_free_all(input, list), 0);
}
