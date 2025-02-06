/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:20:25 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/06 10:37:06 by oloncle          ###   ########.fr       */
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

void	del_hdfiles()
{
	char	*pathname;
	int	i;
	int	ret_unlink;

	i = 1;
	pathname = create_filename(i);
	ret_unlink = unlink(pathname);
	while (!ret_unlink)
	{
		i++;
		free(pathname);
		pathname = create_filename(i);
		ret_unlink = unlink(pathname);
	}
	free(pathname);
}

void	free_parsing(t_lexer **lex_lst, t_data *data, char *line)
{
	if (lex_lst)
		free_lexer(lex_lst);
	if (data->head)
		free_ast(data->head);
	if (line || line[0] != 0)
		free(line);
	del_hdfiles();
}
