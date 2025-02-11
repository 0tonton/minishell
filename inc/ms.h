/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:22:39 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/11 14:36:12 by oloncle          ###   ########.fr       */
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
int	ft_len_word(char *str);
int	ft_strlen(char *s);
size_t	ft_strlcat(char *dst, char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

/*DEBUGGING PRINT*/

void	print_ast(t_node *top_node);
void	print_var_env(char **env);
void	print_lexer_lst(t_lexer **first_node);

/*free*/

void	free_data(t_data *data);
void	free_shlvl(char **env);

/*------------------------------EXECUTION------------------------------*/

extern pid_t	signal_pid;

/*exec.c*/

bool	check_builtin(char *cmd);
void	builtin(t_data *data, t_cmd_node *cmd);
void	do_builtin(t_data *data, t_cmd_node *cmd, int *pipe_fd, int pos);
int		only_cmd(t_data *data, t_cmd_node *cmd);
int		exec(t_data *data, t_node *node);

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

int		if_exist(char *arg, char **env);
int		do_export(t_data *data, char *arg, char **env);
int		check_name(char *name);
void	print_env(char **env);
int		ft_export(t_data *data, char **arg, char **env);

/*pwd.c*/

int		ft_pwd(void);

/*unset.c*/

int		do_unset(t_data *data, char *arg, char **env);
int		ft_unset(t_data *data, char **arg, char **env);

/*do_cmd*/

bool	do_cmd(t_data *data, t_cmd_node *cmd, int pos);
void	child(t_data *data, t_cmd_node *cmd, int pos, int *pipe_fd);
void	parent(t_data *data, int *pipe_fd, int pos);

/*init_path.c*/

int		count_words(char *str, char c);
void	str_copy(char *dest, char *src, int end);
void	set_path(t_data *data, char *cmd, char **path, char **env);
void	simple_path(t_data *data, char *cmd, char **path);
void	init_path(t_data *data, char *cmd, char **path);

/*path_utils.c*/

char	*my_strnstr(char *big, char *little, int len);
int		my_strchr(char *str, char c);
char	**my_split(char *envp, char c);
int		my_strlen(char *str);
void	my_strcat(char *dest, char *src);

/*norme.c*/

void	fill_path(char *path, char *start, char *cmd);
int		check_access(char *path, char **all_paths);
int		search_path(char **env);
void	free_tab(char **tab);
void	ft_swap_str_tab(int i, int j, char **tab);
void	sort_array(char **arr, int len);
int		len_tab(char **tab);
void	env_copy(char ***copy, char **env);

/*libft.c*/

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);

#endif