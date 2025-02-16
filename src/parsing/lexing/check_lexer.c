/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:10:24 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 15:33:52 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/ms.h"

int	check_lex_all_spaces(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if (current->tok_type != T_SPACE)
			return (1);
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
	t_lexer	*cur;

	cur = node;
	while (cur && cur->tok_type == T_SPACE)
		cur = cur->next;
	if (cur && cur->tok_type == T_SENTENCE)
		return (1);
	return (0);
}

int	check_chevrons_and_pipes(t_lexer *current, int *exit_s)
{
	if (current->tok_type == T_PIPE && current->next->tok_type == T_PIPE)
	{
		write(2, "WARNING: double PIPE\n", 21);
		*exit_s = 1;
		return (0);
	}
	if (is_chevrons(current) && (!next_tok_sentence(current->next) \
	|| is_chevrons(current->next)))
	{
		write(2, "ERROR: unexpected token\n", 24);
		*exit_s = 2;
		return (0);
	}
	return (1);
}

int	check_lex_special_char(t_lexer *lex, int *exit_s)
{
	t_lexer	*current;

	current = lex;
	while (current->next)
	{
		if (current->next)
		{
			if (!check_chevrons_and_pipes(current, exit_s))
				return (0);
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
