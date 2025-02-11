/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:35:50 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/11 12:02:55 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexing.h"
#include "../../inc/ms.h"
#include "../../inc/parsing.h"

int	check_lex_all_spaces(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if (current->tok_type != T_SPACE)
			return(1);
		current = current->next;
	}
	return (0);
}

int	is_chevrons(t_lexer *node)
{
	if (node->tok_type == T_DGREAT)
		return (1);
	else if (node->tok_type == T_GREAT)
		return (1);
	else if (node->tok_type == T_LESS)
		return (1);
	else if (node->tok_type == T_DLESS)
		return (1);
	return (0);
}

int	next_tok_sentence(t_lexer *node)
{
	t_lexer *cur;

	cur = node;
	while (cur && cur->tok_type == T_SPACE)
		cur = cur->next;
	if (cur && cur->tok_type == T_SENTENCE)
		return (1);
	return (0);
}

int	check_lex_special_char(t_lexer *lex, int *exit_s)
{
	t_lexer	*current;

	current = lex;
	while (current->next)
	{
		if (current->next)
		{
			if (current->tok_type == T_PIPE && current->next->tok_type == T_PIPE)
			{
				write(2, "WARNING: double PIPE\n", 21);
				*exit_s = 1;
				return (0);
			}
			if (is_chevrons(current) && (!next_tok_sentence(current->next) || is_chevrons(current->next)))
			{
				write(2, "ERROR: unexpected token\n", 24);
				*exit_s = 2;
				return (0);
			}
		}
		current = current->next;
	}
	if (is_chevrons(current) || current->tok_type == T_PIPE)
	{
		write(2, "ERROR: unexpected token at EOL\n", 31);
		*exit_s = 2;
		return (0);
	}
	return (1);
}

void	prompting(t_data *data)
{
	char	*line;
	t_lexer	**lex_lst;

	while (1)
	{
		lex_lst = NULL;
		data->head = NULL;
		line = readline("\033[0;31mminishell>\033[0m ");
		if (line == NULL)
		{
			free_data(data);
			write(2, "exit...\n", 8);
			exit(0);
		}
		else if (line[0] != 0)
		{
			lex_lst = lexer_line(line, &data->exit_status, data->env);
			if (lex_lst && check_lex_all_spaces(*lex_lst))
			{
				//print_lexer_lst(lex_lst);
				add_history(line);
				if (check_lex_special_char(*lex_lst, &(data->exit_status)))
				{
					data->head = creating_tree(lex_lst);
					free_parsing(lex_lst, data, line, 1);
					lex_lst = NULL;
					line = NULL;
					exec(data, data->head);
				}
				//print_ast(data->head);
			}
		}
		free_parsing(lex_lst, data, line, 0);
	}
}
