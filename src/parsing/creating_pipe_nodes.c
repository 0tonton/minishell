/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_pipe_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:09:29 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:57:07 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	count_and_check_pipes(t_lexer **head)
{
	t_lexer	*current;
	int	i;

	current = *head;
	i = 0;
	while (current->next != NULL)
	{
		if (current->tok_type == T_PIPE)
			i++;
		current = current->next;
	}
	if (current->tok_type == T_PIPE || (*head)->tok_type == T_PIPE)
	{
		write(2, "ERROR: invalid PIPE\n", 20);
		return (-1);
	}
	return (i);
}

t_pipe_node	*create_pipe_node()
{
	t_pipe_node	*pipe_node;

	pipe_node = malloc(sizeof(t_pipe_node));
	pipe_node->type = PIPE;
	pipe_node->left = NULL;
	pipe_node->right = NULL;
	return (pipe_node);
}

t_pipe_node	*creating_n_linked_pipe_nodes(int n)
{
	t_pipe_node	*head_pipe;
	t_pipe_node	*next_pipe;
	t_pipe_node	*current;

	head_pipe = malloc(sizeof(t_pipe_node));
	head_pipe->type = PIPE;
	head_pipe->right = NULL;
	head_pipe->left = NULL;
	current = head_pipe;
	while (n > 0)
	{
		next_pipe = create_pipe_node();
		current->left = (t_node *)next_pipe;
		current = next_pipe;
		n--;
	}
	return (head_pipe);
}
