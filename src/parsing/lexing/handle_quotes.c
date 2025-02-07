/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:30:36 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:41:20 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

int	check_quotes_presence(t_lexer *first_node, t_token_type quote_type)
{
	t_lexer *current;

	current = first_node;
	while (current != NULL)
	{
		if (!quote_type && (current->tok_type == T_SQUOTE || current->tok_type == T_DQUOTE))
			return (1);
		else if (current->tok_type == quote_type)
			return (1);
		current = current->next;
	}
	return (0);
}

t_lexer	*quote_node(t_lexer *first_node)
{
	t_lexer *current;
	
	current = first_node;
	while (current != NULL)
	{
		if (current->tok_type == T_SQUOTE || current->tok_type == T_DQUOTE)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_lexer	*replace_node(t_lexer *cating_node, t_lexer *cur_node, char *cat_str)
{
	t_lexer	*new_node;
	char	*new_str;

	new_str = ft_calloc(ft_strlen(cating_node->str) + ft_strlen(cat_str) + 1, sizeof(char));
	new_node = malloc(sizeof(t_lexer));
	ft_strlcat(new_str, cating_node->str, ft_strlen(cating_node->str) + 1);
	ft_strlcat(new_str, cat_str, ft_strlen(new_str) + ft_strlen(cat_str) + 1);
	new_node->str = new_str;
	new_node->next = cur_node->next;
	new_node->prev = cating_node->prev;
	if (cating_node->prev)
		cating_node->prev->next = new_node;
	if (cur_node->next)
		cur_node->next->prev = new_node;
	new_node->tok_type = T_SENTENCE;
	free(cating_node->str);
	free(cating_node);
	return (new_node);
}

void	concat_sentences(t_lexer **first_node)
{
	t_lexer *current;
	t_lexer	*next;

	current = (*first_node)->next;
	while (current != NULL)
	{
		next = current->next;
		if (current->prev->tok_type == T_SENTENCE && current->tok_type == T_SENTENCE)
		{
			if (current->prev->prev)
				current->prev = replace_node(current->prev, current, current->str);
			else
				*first_node = replace_node(current->prev, current, current->str);
			free(current->str);
			free(current);
		}
		current = next;
	}
}

int	handle_quotes(t_lexer **first_node, int e_status, char **env)
{
	t_lexer	*first_quote;
	t_lexer	*last_quote;

	if (!check_quotes_presence(*first_node, 0))
		return (2);
	first_quote = quote_node(*first_node);
	if (check_quotes_presence(first_quote->next, first_quote->tok_type))
	{
		if (first_quote->tok_type == T_DQUOTE)
		{
			last_quote = first_quote->next;
			while (last_quote && last_quote->tok_type != first_quote->tok_type)
			{
				last_quote = last_quote->next;
				last_quote = quote_node(last_quote);
			}
			handle_env_var(first_quote, last_quote, &e_status, env);
		}
		create_and_add_new_node(first_node, first_quote);
		concat_sentences(first_node);
	}
	else
		return (0);
	return (handle_quotes(first_node, e_status, env));
}
