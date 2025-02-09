/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:35:50 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/09 12:31:50 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexing.h"
#include "../../inc/ms.h"
#include "../../inc/parsing.h"

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

// int	check_lex_special_char(t_lexer *lex)
// {
// 	t_lexer	*current;
// 	int	doub_pipe;

// 	doub_pipe = 0;
// 	current = lex;
// 	while (current)
// 	{
// 		if (lex->tok_type == T_PIPE && lex->next && lex->next->tok_type == T_PIPE)
// 			return (0);
// 		if (lex->tok_type == )
// 		current = current->next;
// 	}
// }

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
				//print_lexer_lst(lex_lst);
				add_history(line);
				data->head = creating_tree(lex_lst);
				//print_ast(data->head);
			}
			//data->save_fd1 = -2;
			//data->save_fd0 = -2;
			if (exec(data, data->head) == 0)
				printf("Y'a un problème...\n");
			/*if (data->save_fd0 >= 0)
			{
				dup2(data->save_fd0, 0);
				close(data->save_fd0);
			}
			if (data->save_fd1 >= 0)
			{
				dup2(data->save_fd1, 1);
				close(data->save_fd1);
			}*/
		}
		free_parsing(lex_lst, data, line);
	}
}
