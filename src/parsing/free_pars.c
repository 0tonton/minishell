/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:20:25 by oloncle           #+#    #+#             */
/*   Updated: 2025/01/31 11:21:09 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	free_cmd_node(t_cmd_node *node)
{
	int	i;

	i = 0;
	while ((node->cmd_name)[i])
	{
		free(node->cmd_name[i]);
		i++;
	}
	free(node->cmd_name);
	if (node->input)
		free(node->input);
	if (node->output)
		free(node->output);
	free(node);
}

void	free_ast(t_node *top_node)
{
	t_node	*current;
	t_node	*next_pipe;

	current = top_node;
	if (current->type == CMD)
		free_cmd_node((t_cmd_node *)top_node);
	else
	{
		next_pipe = ((t_pipe_node *)current)->left;
		while (current != NULL && current->type == PIPE)
		{
			if (((t_pipe_node *)current)->left->type == PIPE)
				next_pipe = ((t_pipe_node *)current)->left;
			else
			{
				free_cmd_node((t_cmd_node *)(((t_pipe_node *)current)->left));
				next_pipe = NULL;
			}
			free_cmd_node((t_cmd_node *)(((t_pipe_node *)current)->right));
			free(current);
			current = next_pipe;
		}
	}
}
