/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:47:20 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 12:57:52 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	chevron_output(t_lexer *prev, t_lexer *current, t_cmd_node *cmd_node)
{
	if (prev->tok_type == T_LESS)
	{
		if (cmd_node->heredoc)
			unlink(cmd_node->input);
		if (cmd_node->input)
			free(cmd_node->input);
		if (!current->str)
			return (-1);
		cmd_node->input = ft_strdup(current->str);
		cmd_node->heredoc = 0;
	}
	else if (prev->tok_type == T_DLESS)
	{
		if (cmd_node->heredoc)
			unlink(cmd_node->input);
		if (cmd_node->input)
			free(cmd_node->input);
		cmd_node->input = ft_strdup(current->str);
		cmd_node->heredoc = 1;
	}
	else
		return (0);
	return (1);
}

int	chevron_input(t_lexer *prev, t_lexer *current, t_cmd_node *cmd_node)
{
	if (prev->tok_type == T_GREAT)
	{
		if (cmd_node->output)
			free(cmd_node->output);
		if (!current->str)
			return (-1);
		cmd_node->output = ft_strdup(current->str);
		cmd_node->append_mode = 0;
	}
	else if (prev->tok_type == T_DGREAT)
	{
		if (cmd_node->output)
			free(cmd_node->output);
		if (!current->str)
			return (-1);
		cmd_node->output = ft_strdup(current->str);
		cmd_node->append_mode = 1;
	}
	else
		return (0);
	return (1);
}

int	if_chevron(t_lexer *current, t_cmd_node *cmd_node)
{
	t_lexer	*prev;
	int		ret;

	prev = current->prev;
	while (prev && prev->tok_type == T_SPACE)
		prev = prev->prev;
	if (prev)
	{
		ret = chevron_input(prev, current, cmd_node);
		if (!ret)
			return (chevron_output(prev, current, cmd_node));
		return (ret);
	}
	return (1);
}
