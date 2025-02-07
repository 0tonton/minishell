/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifying_tok_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:14:15 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:40:47 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

void	if_space(t_lexer *first_node, char *line, int *i)
{
	char	*str_space;

	str_space = malloc(sizeof(char) * 2);
	if (ft_is_space(line[*i]))
	{
		str_space[0] = line[*i];
		str_space[1] = '\0';
		(*i)++;
		add_lexer_node(first_node, str_space, T_SPACE);
	}
	free(str_space);
}

void	pipe_tok(t_lexer *first_node, char *line, int *i)
{
	if (line[*i] == '|')
	{
		(*i)++;
		add_lexer_node(first_node, "|", T_PIPE);
	}
}

void	if_operator(t_lexer *first_node, char *line, int *i)
{
	if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
		{
			add_lexer_node(first_node, ">>", T_DGREAT);
			(*i)++;
		}
		else
			add_lexer_node(first_node, ">", T_GREAT);
	}
	else if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
		{
			add_lexer_node(first_node, "<<", T_DLESS);
			(*i)++;
		}
		else
			add_lexer_node(first_node, "<", T_LESS);
	}
	else
		pipe_tok(first_node, line, i);
}
