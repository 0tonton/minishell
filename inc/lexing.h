/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:33:26 by oloncle           #+#    #+#             */
/*   Updated: 2025/01/30 16:56:00 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

#include "ms.h"

//STRUCT

typedef enum e_token_type
{
	T_SENTENCE = 1,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_SQUOTE,
	T_DQUOTE,
	T_VAR,
	T_SPACE,
}	t_token_type;

//inquote to know if we're already in quote or not and waiting for la suite du prompt
typedef struct s_lexer
{
	t_token_type		tok_type;
	char			*str;

	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;


//FCTS
	//////LEXER//////
t_lexer	**lexer_line(char *line);
void	add_lexer_node(t_lexer *first_node, char *value, t_token_type tok_type);
void	free_lexer(t_lexer **first_node);

	//identifying token 
void	if_var(t_lexer *first_node, char *line, int *i);
void	if_sentence(t_lexer *first_node, char *line, int *i);
void	if_quote(t_lexer *first_node, char *line, int *i);
void	if_space(t_lexer *first_node, char *line, int *i);
void	if_operator(t_lexer *first_node, char *line, int *i);

	//handle quotes
int	handle_quotes(t_lexer **first_node);
void	create_and_add_new_node(t_lexer **first_node, t_lexer *first_quote);

	//utils
int	ft_is_space(char c);
int	is_special(char c);


void	print_lexer_lst(t_lexer **first_node);

#endif