/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:31:08 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/17 08:49:51 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	print_struckt(t_input *input)
{
	int	i;

	if (input->entrada)
		printf("entrada --> %s\n", input->entrada);
	if (input->itxt && input->itxt[1] != 0)
		printf("inputtxt --> %s\n", input->itxt[1]);
	if (input->otxt && input->otxt[1] != 0)
		printf("outputtxt --> %s\n", input->otxt[1]);
	if (input->itxt && input->itxt[0] != 0)
		printf("simbolo inputtxt --> %s\n", input->itxt[0]);
	if (input->otxt && input->otxt[0] != 0)
		printf("simbolo outputtxt --> %s", input->otxt[0]);
	i = 0;
	while (input->commd && input->commd[i] && input->commd[i][0] != 0)
	{
		printf("\n%dcomandos -->", i);
		printf(" %s", input->commd[i]);
		i++;
	}
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	t_input	*input;
	char	**argv;
	t_env	*list;

	(void)ac;
	(void)av;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	list = (t_env *)malloc(sizeof(t_env));
	input = malloc(sizeof(t_input));
	input->pipex = malloc(sizeof(t_pipex));
	input->pipex->env = env;
	fill_up_env(env, &list);
	while (1)
	{
		input->entrada = readline("minishell> ");
		if (input->entrada == NULL)
			break ;
		if (*input->entrada != 0)
			add_history (input->entrada);
		else
			continue ;
		if (check_input(input->entrada) != 0)
		{
			printf("INPUT ERROR\n");
			continue ;
		}
		change_caracter(input);
		input->entrada = add_space(input->entrada, '|');
		input->entrada = add_space(input->entrada, '<');
		input->entrada = add_space(input->entrada, '>');
		argv = input_split(input -> entrada, &list);
		fill_up_input(argv, input);
		free(input -> entrada);
		ft_pipex(input, &list);
	}
	return (0);
}
