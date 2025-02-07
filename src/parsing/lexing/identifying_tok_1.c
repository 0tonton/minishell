/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifying_tok_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:07:27 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:40:51 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

void	if_var(t_lexer *first_node, char *line, int *i)
{
	int	len_word;
	char	*str;
	int	j;

	if (line[*i] != '$')
		return ;
	j = 1;
	len_word = ft_len_word(line + *i + 1);
	str = malloc(sizeof(char) * (len_word + 2));
	str[0] = line[*i];
	(*i)++;
	while (line[*i] && !ft_is_space(line[*i]) && !is_special(line[*i]))
	{
		str[j] = line[*i];
		(*i)++;
		j++;
	}
	str[j] = '\0';
	add_lexer_node(first_node, str, T_VAR);
	free(str);
}

void	if_sentence(t_lexer *first_node, char *line, int *i)
{
	char	*str;
	int	j;
	int	len_sentence;

	len_sentence = ft_len_word(line + *i);
	if (len_sentence > 0)
	{
		str = malloc(sizeof(char) * (len_sentence + 1));
		j = 0;
		while (line[*i] && !ft_is_space(line[*i]) && !is_special(line[*i]))
		{
			str[j] = line[*i];
			j++;
			(*i)++;
		}
		str[j] = '\0';
		add_lexer_node(first_node, str, T_SENTENCE);
		free(str);
	}
}

void	if_quote(t_lexer *first_node, char *line, int *i)
{
	if (line[*i] == '\'')
	{
		add_lexer_node(first_node, "'", T_SQUOTE);
		(*i)++;
	}
	else if (line[*i] == '"')
	{
		add_lexer_node(first_node, "\"", T_DQUOTE);
		(*i)++;
	}
}

// void	if_nl(t_lexer *first_node, char *line, int *i)
// {
// 	if (line[*i] == '\n')
// 	{
// 		(*i)++;
// 		add_lexer_node(first_node, "\n", T_NL);
// 	}
// }
