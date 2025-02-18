/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:40:57 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/18 11:46:55 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/parsing.h"
#include "../../../inc/ms.h"

char	*handling_exit_status(char *node_str, int *e_status)
{
	char	*new_str;
	char	*temp;

	new_str = NULL;
	if (node_str[1] == '?')
	{
		temp = ft_itoa(*e_status);
		new_str = assiging_new_str(temp, node_str);
		free(temp);
	}
	else if (!ft_strncmp(node_str, "$EMPTY", 6))
	{
		if (node_str[6] == '?')
			new_str = ft_strdup(node_str + 6);
		else
			new_str = ft_calloc(1, sizeof(char));
		*e_status = 0;
	}
	free(node_str);
	return (new_str);
}

char	*ft_getenv(char *name, char **env)
{
	int		len;
	char	*cur_var;
	int		i;

	i = 0;
	cur_var = *env;
	len = len_var(name);
	while (cur_var)
	{
		if (len == len_var(cur_var) && !ft_strncmp(cur_var, name, len))
			return (cur_var + len + 1);
		i++;
		cur_var = env[i];
	}
	return (NULL);
}

int	check_for_interrogation(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '?')
			return (i);
		i++;
	}
	return (-1);
}

char	*handle_long_var(char *copy, char **env)
{
	int		len;
	char	*temp;
	char	*ret;
	char	*cpy_cpy;

	len = check_for_interrogation(copy);
	if (len == -1)
		return (ft_strdup(ft_getenv(copy, env)));
	cpy_cpy = ft_strdup(copy);
	copy[len] = '\0';
	temp = ft_strdup(ft_getenv(copy, env));
	ret = ft_calloc(ft_strlen(temp) + ft_strlen(cpy_cpy + len) + 1, \
	sizeof(char));
	ft_strlcat(ret, temp, ft_strlen(temp) + 1);
	ft_strlcat(ret, cpy_cpy + len, ft_strlen(ret) + \
	ft_strlen(cpy_cpy + len) + 1);
	free(cpy_cpy);
	free(temp);
	return (ret);
}

void	handle_env_var(t_lexer *start, t_lexer *end, int *e_status, char **env)
{
	t_lexer	*node;
	char	*copy;

	node = start;
	while (node && node != end)
	{
		if (node->tok_type == T_VAR)
		{
			copy = ft_strdup((node->str) + 1);
			if (copy[0])
			{
				node->str = handling_exit_status(node->str, \
				e_status);
				if (node->str == NULL)
					node->str = handle_long_var(copy, env);
			}
			free(copy);
			node->tok_type = T_SENTENCE;
		}
		node = node->next;
	}
}
