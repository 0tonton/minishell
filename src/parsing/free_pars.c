/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klabaune <klabaune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:20:25 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/18 16:31:25 by klabaune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

void	free_cmd_node(t_cmd_node *node)
{
	int	i;

	i = 0;
	if (node)
	{
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
	top_node = NULL;
}

void	del_hdfiles(void)
{
	char	*pathname;
	int		i;
	int		ret_unlink;

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

void	free_parsing(t_lexer **lex_lst, t_data *data, \
char *line, int before_exec)
{
	if (lex_lst)
		free_lexer(lex_lst);
	if (data->head && !before_exec)
		free_ast(data->head);
	if (!line || line[0] != 0 || line[0] != 4)
		free(line);
	if (!before_exec)
		del_hdfiles();
}
