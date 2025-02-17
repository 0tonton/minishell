/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:35:50 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/17 16:13:19 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexing.h"
#include "../../inc/ms.h"
#include "../../inc/parsing.h"

int	managing_line(t_lexer **lex_lst, char **line, t_data *data)
{
	if (lex_lst && check_lex_all_spaces(*lex_lst))
	{
		add_history(*line);
		if (check_lex_special_char(*lex_lst, &(data->exit_status)))
		{
			data->head = creating_tree(lex_lst);
			free_parsing(lex_lst, data, *line, 1);
			*line = NULL;
			exec(data, data->head);
			set_up_signals();
			g_signal_pid = 0;
			return (1);
		}
	}
	g_signal_pid = 0;
	return (0);
}

void	prompting(t_data *data)
{
	char	*line;
	t_lexer	**lex_lst;
	int		exit_s;

	while (1)
	{
		lex_lst = NULL;
		data->head = NULL;
		data->prev_pipe_fd0 = -1;
		line = readline("\033[0;31mminishell>\033[0m ");
		if (line == NULL)
		{
			exit_s = data->exit_status;
			free_data(data);
			write(2, "exit...\n", 8);
			exit(exit_s);
		}
		else if (line[0] != 0)
		{
			lex_lst = lexer_line(line, &data->exit_status, data->env);
			if (managing_line(lex_lst, &line, data))
				lex_lst = NULL;
		}
		free_parsing(lex_lst, data, line, 0);
	}
}
