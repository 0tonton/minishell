/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:45:01 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 12:27:36 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

void	free_lexer(t_lexer **first_node)
{
	t_lexer	*current_node;
	t_lexer	*next_node;

	current_node = *first_node;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		if (current_node->str)
			free(current_node->str);
		free(current_node);
		current_node = next_node;
	}
	free(first_node);
}

int	ft_is_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\r' \
	|| c == '\f' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '<' || c == '>' \
	|| c == '|' || c == '$' \
	|| c == '\'' || c == '"')
		return (1);
	return (0);
}
