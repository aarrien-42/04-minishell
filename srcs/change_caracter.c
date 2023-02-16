/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_caracter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubegona <ubegona@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:59:48 by ubegona           #+#    #+#             */
/*   Updated: 2023/02/16 09:26:19 by ubegona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	change_caracter(t_input *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input -> entrada[i])
	{
		if (quote == 0
			&& (input->entrada[i] == '\'' || input->entrada[i] == '\"'))
			quote = input->entrada[i];
		else if (quote != 0 && input->entrada[i] == quote)
			quote = 0;
		if (quote != 0 && input->entrada[i] == '<')
			input->entrada[i] = 18;
		if (quote != 0 && input->entrada[i] == '>')
			input->entrada[i] = 17;
		if (quote != 0 && input->entrada[i] == '|')
			input->entrada[i] = 16;
		i++;
	}
}
