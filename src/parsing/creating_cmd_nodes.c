/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:32:26 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 12:57:32 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	nb_cmd_arg(t_lexer *first_lex_node)
{
	int		i;
	t_lexer	*current;

	i = 0;
	current = first_lex_node;
	while (current != NULL && current->tok_type != T_PIPE)
	{
		if (current->tok_type == T_SENTENCE)
		{
			if (current->prev == NULL \
	|| (current->prev != NULL && current->prev->tok_type != T_LESS \
	&& current->prev->tok_type != T_DLESS \
	&& current->prev->tok_type != T_DGREAT \
	&& current->prev->tok_type != T_GREAT))
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
	node->del_cmd = 0;
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

t_node	*create_cmd_node(t_lexer *first_lex_node)
{
	t_cmd_node	*cmd_node;
	t_lexer		*current;
	int			ret_chevron;

	cmd_node = malloc(sizeof(t_cmd_node));
	init_cmd_node(cmd_node, first_lex_node);
	current = first_lex_node;
	while (current != NULL && current->tok_type != T_PIPE)
	{
		if (current->tok_type == T_SENTENCE)
		{
			ret_chevron = if_chevron(current, cmd_node);
			if (ret_chevron == -1)
			{
				free(cmd_node);
				return (NULL);
			}
			if (current->prev == NULL || \
			(current->prev != NULL && !ret_chevron))
				add_str_to_lst(cmd_node->cmd_name, current->str);
		}
		current = current->next;
	}
	return ((t_node *)cmd_node);
}
