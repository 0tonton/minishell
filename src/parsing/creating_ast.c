/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:43:00 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 15:51:13 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

t_lexer	*prev_lex(t_lexer *current_lex)
{
	t_lexer	*lex_node;

	if (!current_lex || current_lex->prev == NULL)
		return (NULL);
	lex_node = current_lex->prev;
	while (lex_node->prev != NULL && lex_node->prev->tok_type != T_PIPE)
		lex_node = lex_node->prev;
	return (lex_node);
}

t_lexer	*last_lex(t_lexer *head)
{
	t_lexer	*last;

	last = head;
	while (last->next != NULL)
		last = last->next;
	while (last->prev != NULL && last->prev->tok_type != T_PIPE)
		last = last->prev;
	if (last->prev == NULL)
		return (NULL);
	return (last);
}

void	creating_rl_cmd_nodes(t_pipe_node *current_p, t_lexer **current_lex)
{
	if (current_p->right == NULL)
	{
		printf("Creating right CMD node...\n");
		current_p->right = create_cmd_node(*current_lex);
		*current_lex = prev_lex(*current_lex);
	}
	if (current_p->left == NULL)
	{
		printf("Creating left CMD node...\n");
		current_p->left = create_cmd_node(*current_lex);
		*current_lex = prev_lex(*current_lex);
	}
}

t_node	*creating_tree(t_lexer **head)
{
	int	nb_pipes;
	t_pipe_node	*top;
	t_pipe_node	*current_p;
	t_lexer		*current_lex;

	current_lex = last_lex(*head);
	current_p = NULL;
	nb_pipes = count_and_check_pipes(head);
	if (nb_pipes == -1)
		return (NULL);
	if (nb_pipes == 0)
		return ((t_node *)(create_cmd_node(*head)));
	top = creating_n_linked_pipe_nodes(nb_pipes - 1);
	current_p = top;
	while (nb_pipes > 0)
	{
		creating_rl_cmd_nodes(current_p, &current_lex);
		if (!current_p->left || !current_p->right)
		{
			free_ast((t_node *)top);
			return (NULL);
		}
		current_p = (t_pipe_node *)current_p->left;
		nb_pipes--;
	}
	return ((t_node *)top);
}
