/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:22:39 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 18:28:06 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <errno.h>
# include "lexing.h"
# include "parsing.h"

/*------------------------------MAIN------------------------------*/

/*main loop - prompting*/

void	prompting(t_data *data);

/*signals*/

void	set_up_signals(void);

/*------------------------------PARSING------------------------------*/

/*libft utils*/

char	*ft_strdup(char *s);
int		ft_len_word(char *str);
int		ft_strlen(char *s);
size_t	ft_strlcat(char *dst, char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*DEBUGGING PRINT*/

void	print_ast(t_node *top_node);
void	print_var_env(char **env);
void	print_lexer_lst(t_lexer **first_node);

/*free*/

void	free_data(t_data *data);

/*------------------------------EXECUTION------------------------------*/

extern pid_t	g_signal_pid;

/*exec.c*/

bool	check_builtin(char *cmd);
void	builtin(t_data *data, t_cmd_node *cmd);
void	do_builtin(t_data *data, t_cmd_node *cmd, int *pipe_fd, int pos);
int		exec(t_data *data, t_node *node);

/* exec_utils.c */

int		open_outfile_bin(t_cmd_node *cmd, int pos, int *pipe_fd);
int		open_infile_bin(t_cmd_node *cmd, int pos, t_data *data);
void	wait_all(t_data *data);
void	open_outfile(t_cmd_node *cmd, int pos, int *pipe_fd, int save_fd1);
void	open_infile(t_cmd_node *cmd, int pos, int save_fd1, t_data *data);

/*cd.c*/

void	change_oldpwd(t_data *data);
void	error_malloc(void);
void	change_pwd(t_data *data, char *path);
int		ft_cd(t_data *data, char **arg);

/*echo.c*/

int		check_flag_n(char *arg);
int		ft_echo(char **arg);

/*env.c*/

int		ft_env(char **env);

/*exit.c*/

int		simili_atoi(char *str, int *check);
void	ft_exit(t_data *data, char **arg);

/*export.c*/

int		new_export(char **env, char *arg, t_data *data);
int		old_export(char ***tmp, char **env, char *arg, int pos);
int		do_export(t_data *data, char *arg, char **env);
void	print_env(char **env);
int		ft_export(t_data *data, char **arg, char **env);

/*pwd.c*/

int		ft_pwd(void);

/*unset.c*/

int		really_do_unset(char ***tmp, char **env, int pos);
int		do_unset(t_data *data, char *arg, char **env);
int		ft_unset(t_data *data, char **arg);

/* builtin_utils.c */

int		check_name(char *name);
int		if_exist(char *arg, char **env);
int		copy_env(char **tmp, char *cpy);

/*do_cmd*/

void	child(t_data *data, t_cmd_node *cmd, int pos, int *pipe_fd);
void	parent(t_data *data, int *pipe_fd, int pos);
bool	the_fork(t_data *data, t_cmd_node *cmd, int pos, int *pipe_fd);
bool	do_cmd(t_data *data, t_cmd_node *cmd, int pos);

/*init_path.c*/

void	str_copy(char *dest, char *src, int end);
void	good_path(char **path, char *check);
void	set_path(char *cmd, char **path, char **env);
void	simple_path(char *cmd, char **path);
void	init_path(t_data *data, char *cmd, char **path);

/*path_utils.c*/

char	*my_strnstr(char *big, char *little, int len);
int		my_strchr(char *str, char c);
int		count_words(char *str, char c);
char	**my_split(char *envp, char c);
void	my_strcat(char *dest, char *src);

/*utils1.c*/

void	fill_path(char *path, char *start, char *cmd);
int		check_access(char *path, char **all_paths);
int		search_path(char **env);
void	free_tab(char **tab);
char	**clean(char **tab);

/* utils2.c */

void	ft_swap_str_tab(int i, int j, char **tab);
void	sort_array(char **arr, int len);
int		len_tab(char **tab);

/*libft.c*/

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);

#endif
