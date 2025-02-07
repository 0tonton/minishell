/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:22:39 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 11:44:53 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "parsing.h"
#include "lexing.h"

/* // // // // Global data struct // // // */
/*// // // // // // // // // //  // // // */
// typedef	struct	s_data
// {
// 	t_node	*head;
// 	char	**env;
// 	int	exit_status;
// }	t_data;

//	MAIN
	//main loop - prompting
void	prompting(t_data *data);

	//signals
void	set_up_signals(void);

//	PARSING
	//libft utils
char	*ft_strdup(char *s);
int	ft_len_word(char *str);
int	ft_strlen(char *s);
size_t	ft_strlcat(char *dst, char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

//	DEBUGGING PRINT
void	print_ast(t_node *top_node);
void	print_var_env(char **env);
void	print_lexer_lst(t_lexer **first_node);

#endif