/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:32:26 by oloncle           #+#    #+#             */
/*   Updated: 2025/01/31 14:03:17 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	nb_cmd_arg(t_lexer *first_lex_node)
{
	int	i;
	t_lexer	*current;

	i = 0;
	current = first_lex_node;
	while (current != NULL && current->tok_type != T_PIPE)
	{
		if (current->tok_type == T_SENTENCE)
		{
			if (current->prev == NULL ||\
	(current->prev != NULL && current->prev->tok_type != T_LESS && current->prev->tok_type != T_DLESS \
	&& current->prev->tok_type != T_DGREAT && current->prev->tok_type != T_GREAT))
				i++;
		}
		current = current->next;
	}
	return (i);
}

void	init_cmd_node(t_cmd_node *node, t_lexer *first_lex_node)
{
	node->type = CMD;
	node->append_mode = 0;
	node->heredoc = 0;
	node->cmd_name = malloc(sizeof(char *) * (nb_cmd_arg(first_lex_node) + 1));
	node->cmd_name[0] = NULL;
	node->input = NULL;
	node->output = NULL;
}

void	add_str_to_lst(char **lst, char *str)
{
	int	i;

	i = 0;
	while (lst[i] != NULL)
		i++;
	lst[i] = ft_strdup(str);
	lst[i + 1] = NULL;
}

int	if_chevron(t_lexer *current, t_cmd_node *cmd_node)
{
	t_lexer	*prev;

	prev = current->prev;
	while (prev && prev->tok_type == T_SPACE)
		prev = prev->prev;
	if (prev->tok_type == T_GREAT)
		cmd_node->output = ft_strdup(current->str);
	else if (prev->tok_type == T_DGREAT)
	{
		cmd_node->output = ft_strdup(current->str);
		cmd_node->append_mode = 1;
	}
	else if (prev->tok_type == T_LESS)
		cmd_node->input = ft_strdup(current->str);
	else if (prev->tok_type == T_DLESS)
	{
		cmd_node->input = ft_strdup(current->str);
		cmd_node->heredoc = 1;
		//heredoc
	}
	else
		return (0);	
	return (1);
}

t_node	*create_cmd_node(t_lexer *first_lex_node)
{
	t_cmd_node	*cmd_node;
	t_lexer		*current;

	cmd_node = malloc(sizeof(t_cmd_node));
	init_cmd_node(cmd_node, first_lex_node);
	current = first_lex_node;
	while (current != NULL && current->tok_type != T_PIPE)
	{
		if (current->tok_type == T_SENTENCE)
		{
			if (current->prev == NULL || (current->prev != NULL && !(if_chevron(current, cmd_node))))
				add_str_to_lst(cmd_node->cmd_name, current->str);
		}
		current = current->next;
	}
	return ((t_node *)cmd_node);
}
