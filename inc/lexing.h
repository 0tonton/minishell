/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:33:26 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 13:16:10 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

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

typedef struct s_lexer
{
	t_token_type		tok_type;
	char			*str;

	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;


//FCTS
	//////LEXER//////
t_lexer	**lexer_line(char *line, int *e_status, char **env);
void	add_lexer_node(t_lexer *first_node, char *value, t_token_type tok_type);
void	free_lexer(t_lexer **first_node);

	//identifying token 
void	if_var(t_lexer *first_node, char *line, int *i);
void	if_sentence(t_lexer *first_node, char *line, int *i);
void	if_quote(t_lexer *first_node, char *line, int *i);
void	if_space(t_lexer *first_node, char *line, int *i);
void	if_operator(t_lexer *first_node, char *line, int *i);

	//handle quotes
int	handle_quotes(t_lexer **first_node, int e_status, char **env);
void	create_and_add_new_node(t_lexer **first_node, t_lexer *first_quote);

	//handle heredoc
int	manage_hd(t_lexer **head);
int	check_dless(t_lexer *head);

	//heredoc utils
char	*find_delim(t_lexer *head);
int	check_delim_char(t_lexer *node);
t_lexer	*dless_node(t_lexer *head);
void	add_new_node_filename(t_lexer **head, int nb_hd);
char	*create_filename(int nb_hd);

	//handle env var
void	handle_env_var(t_lexer *start, t_lexer *end, int *e_status, char **env);
char	*ft_getenv(char *name, char **env);

	//check lexer
int	check_lex_special_char(t_lexer *lex, int *exit_s);
int	check_lex_all_spaces(t_lexer *head);

	//utils
int	ft_is_space(char c);
int	is_special(char c);
char	*ft_itoa(int n);

void	print_lexer_lst(t_lexer **first_node);

#endif