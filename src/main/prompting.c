/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:35:50 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 11:39:35 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	check_lex_all_spaces(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current)
	{
		if (current->tok_type != T_SPACE)
			return(1);
		current = current->next;
	}
	return (0);
}

void	prompting(t_data *data)
{
	char	*line;
	t_lexer	**lex_lst;

	while (1)
	{
		lex_lst = NULL;
		data->head = NULL;
		line = readline("\033[0;31mminishell>\033[0m ");
		if (line == NULL)
		{
			free_data(data);
			write(1, "exit...\n", 8);
			exit(0);
		}
		else if (line[0] != 0)
		{
			lex_lst = lexer_line(line, &data->exit_status, data->env);
			if (lex_lst && check_lex_all_spaces(*lex_lst))
			{
				add_history(line);
				data->head = creating_tree(lex_lst);
			}
		}
		free_parsing(lex_lst, data, line);
	}
}
