/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:59:55 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/04 16:01:50 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"

int	check_dless(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if (current->tok_type == T_DLESS)
			return (1);
		current =  current->next;
	}
	return (0);
}

int	check_delim_char(t_lexer *node)
{
	if (node->tok_type == T_SPACE || node->tok_type == T_GREAT \
	|| node->tok_type == T_LESS || node->tok_type == T_DGREAT \
	|| node->tok_type == T_DLESS)
		return (0);
	else
		return (1);
}

int	len_delim(t_lexer *start_delim)
{
	int	len;
	t_lexer	*current;

	current = start_delim;
	if (!current)
		return (0);
	len = ft_strlen(start_delim->str);
	while (current->next && check_delim_char(current->next))
	{
		len += ft_strlen(current->str);
		current = current->next;
	}
	return (len);
}

t_lexer	*dless_node(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if ((current)->tok_type == T_DLESS)
			return (current);
		(current) =  (current)->next;
		
	}
	return (NULL);
}

char	*find_delim(t_lexer *head)
{
	t_lexer *start_delim_node;
	char	*delim;

	start_delim_node = dless_node(head);
	start_delim_node = start_delim_node->next;
	while (start_delim_node && start_delim_node->tok_type == T_SPACE)
		start_delim_node = start_delim_node->next;
	delim = ft_calloc(len_delim(start_delim_node) + 1, sizeof(char));
	while (start_delim_node && check_delim_char(start_delim_node))
	{
		ft_strlcat(delim, start_delim_node->str, ft_strlen(delim) + ft_strlen(start_delim_node->str) + 1);
		start_delim_node = start_delim_node->next;
	}
	return (delim);
}
