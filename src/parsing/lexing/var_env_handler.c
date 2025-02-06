/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:40:57 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/06 10:34:38 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"

char	*handling_exit_status(char *node_str, int *e_status)
{
	char	*new_str;
	char	*temp;

	new_str = NULL;
	if (node_str[1] == '?' && node_str[2] == 0)
	{
		temp = ft_itoa(*e_status);
		new_str = ft_strdup(temp);
		free(temp);
	}
	else if (!ft_strncmp(node_str, "$EMPTY", 6) && ft_strlen(node_str) == 6)
	{
		new_str = ft_calloc(1, sizeof(char));
		*e_status = 0;
	}
	free(node_str);
	return (new_str);
}

void	handle_env_var(t_lexer *start, t_lexer *end, int *e_status)
{
	t_lexer	*node;
	char	*copy;

	node = start;
	while (node && node != end)
	{
		if (node->tok_type == T_VAR)
		{
			copy = ft_strdup((node->str) + 1);
			node->str = handling_exit_status(node->str, e_status);
			if (node->str == NULL)
				node->str = ft_strdup(getenv(copy));
			free(copy);
			node->tok_type = T_SENTENCE;
		}
		node = node->next;
	}
}
