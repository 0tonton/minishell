/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:45:01 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:41:22 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

int	len_new_str(t_lexer *first_quote)
{
	t_lexer	*current;
	int	len;

	current = first_quote->next;
	len = 0;
	while (current && current->tok_type != first_quote->tok_type)
	{
		len += ft_strlen(current->str);
		current = current->next;
	}
	return (len);
}

char	*create_new_str(t_lexer *first_quote)
{
	char *str;
	t_lexer	*current;

	current = first_quote->next;
	str = ft_calloc(len_new_str(first_quote) + 1, sizeof(char));
	while (current && current->tok_type != first_quote->tok_type)
	{
		ft_strlcat(str, current->str, ft_strlen(str) + ft_strlen(current->str) + 1);
		current = current->next;
	}
	return (str);
}

t_lexer	*del_until_sec_quote(t_lexer *first_quote)
{
	t_lexer	*current;
	t_lexer	*next;
	t_token_type quote_type;

	quote_type = first_quote->tok_type;
	current = first_quote->next;
	while (current->tok_type != quote_type)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next;
	}
	return (current);
}

void	create_and_add_new_node(t_lexer **first_node, t_lexer *first_quote)
{
	t_lexer	*new_node;
	t_lexer	*sec_quote;

	new_node = malloc(sizeof(t_lexer));
	new_node->str = create_new_str(first_quote);
	new_node->tok_type = T_SENTENCE;
	new_node->prev = first_quote->prev;
	if (first_quote->prev)
		(first_quote->prev)->next = new_node;
	sec_quote = del_until_sec_quote(first_quote);
	if (sec_quote->next)
		(sec_quote->next)->prev = new_node;
	new_node->next = sec_quote->next;
	if (sec_quote->str)
		free(sec_quote->str);
	free(sec_quote);
	free(first_quote->str);
	free(first_quote);
	if (!new_node->prev)
		*first_node = new_node;
	else
		first_quote = new_node;
}
