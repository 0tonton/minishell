/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:52:57 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/04 17:01:58 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"

t_lexer	*init_lexer_list()
{
	t_lexer	*first_node;

	first_node = malloc(sizeof(t_lexer));
	first_node->str = NULL;
	first_node->next = NULL;
	first_node->prev = NULL;
	return (first_node);
}

void	add_lexer_node(t_lexer *first_node, char *value, t_token_type tok_type)
{
	t_lexer *next_node;
	t_lexer *current_node;

	if (first_node->str == NULL)
	{
		first_node->str = ft_strdup(value);
		first_node->tok_type = tok_type;
	}
	else
	{
		next_node = malloc(sizeof(t_lexer));
		current_node = first_node;
		while (current_node->next != NULL)
			current_node = current_node->next;
		next_node->str = ft_strdup(value);
		next_node->tok_type = tok_type;
		next_node->next = NULL;
		next_node->prev = current_node;
		current_node->next = next_node;
	}
}

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

void	identifying_token(t_lexer *lexer_lst, char *line, int *i)
{
	if_space(lexer_lst, line, i);
	if_operator(lexer_lst, line, i);
	if_var(lexer_lst, line, i);
	if_quote(lexer_lst, line, i);
	if_sentence(lexer_lst, line, i);
}

t_lexer	**lexer_line(char *line)
{
	int	i;
	t_lexer	**lexer_lst;
	
	i = 0;
	lexer_lst = malloc(sizeof(t_lexer *));
	*lexer_lst = init_lexer_list();
	while (line[i] != '\0')
	{
		if (line[i])
			identifying_token(*lexer_lst, line, &i);
	}
	if (check_dless(*lexer_lst))
	{
		
		if (!manage_hd(lexer_lst))
		{
			free_lexer(lexer_lst);
			write(2, "ERROR: no DELIMETER given\n", 26);
			return (NULL);
		}
	}
	//print_lexer_lst(lexer_lst);
	//heredoc
	//expander
	//handle quote
	//create files from redir
	if (!handle_quotes(lexer_lst))
	{
		free_lexer(lexer_lst);
		write(2, "ERROR: quotes unclosed\n", 23);
		return (NULL);
	}
	return (lexer_lst);
}
