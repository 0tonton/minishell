/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:22:39 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/03 17:16:05 by oloncle          ###   ########.fr       */
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
#include "ms.h"

//	PARSING
	//libft utils
char	*ft_strdup(char *s);
int	ft_len_word(char *str);
int	ft_strlen(char *s);
size_t	ft_strlcat(char *dst, char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif