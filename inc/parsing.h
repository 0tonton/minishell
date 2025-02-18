/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:50:10 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 15:49:37 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*------------------------------STRUCT------------------------------*/

enum e_type
{
	CMD = 0,
	PIPE = 1
};

typedef struct s_node
{
	enum e_type	type; //CMD or PIPE
}	t_node;

typedef struct s_cmd_node
{
	enum e_type	type; // 0
	char		**cmd_name; //liste de la cmd avec ses arguments, fini par NULL
	char		*input; //NULL if stdin, sinon nom du fichier
	char		*output; //NULL si stdout, sinon nom du fichier
	int			append_mode; //0 si pas d'append, sinon 1
	int			heredoc; //0 si pas here doc, sinon 1
	int			del_cmd;
}	t_cmd_node;

typedef struct s_pipe_node
{
	enum e_type	type; //1
	t_node		*right; //soit pipe_node, soit cmd_node
	t_node		*left; //soit pipe_node, soit cmd_node
}	t_pipe_node;

typedef struct s_data
{
	t_node	*head;
	char	**env;
	int		exit_status;
	int		act_pipe_fd0;
	int		prev_pipe_fd0;
}	t_data;

/*------------------------------FUNCTIONS------------------------------*/
/*Creating ast & free*/
t_node		*creating_tree(t_lexer **head);
void		free_ast(t_node *top_node);
void		free_parsing(t_lexer **lex_lst, t_data *data, char *line, \
int before_exec);
void		del_hdfiles(void);

/*LIBFT utils*/
int			is_in_str(char c, char *str);
int			start_i(char const *s, char *c);
void		end_var(char const *s, char *c, int *end);
char		**ft_split(char const *s, char *c);
int			ft_atoi(const char *nptr);

/*cmd nodes*/
t_node		*create_cmd_node(t_lexer *first_lex_node);
int			if_chevron(t_lexer *current, t_cmd_node *cmd_node);

/*pipe nodes*/
t_pipe_node	*creating_n_linked_pipe_nodes(int n);
int			count_and_check_pipes(t_lexer **head);

/*Env variables*/
char		**tab_var_env(char **og_env);
int			len_var(char *var);

/*parsing utils*/
int			count_cmd(t_node *head_node);

#endif