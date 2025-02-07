/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:03:33 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:40:54 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

void	del_node(t_lexer **head, t_lexer *del_node)
{
	(void)(head);
	if (del_node->prev)
		del_node->prev->next = del_node->next;
	if (del_node->next)
		del_node->next->prev = del_node->prev;
	free(del_node->str);
	free(del_node);
}

char	*create_filename(int nb_hd)
{
	char	*filename;
	char	*nb;
	int	len;

	nb = ft_itoa(nb_hd);
	len = ft_strlen(nb) + ft_strlen("hd_.txt") + 1;
	filename = ft_calloc(len, sizeof(char));
	ft_strlcat(filename, "hd_", 4);
	ft_strlcat(filename, nb, ft_strlen(nb) + ft_strlen(filename) + 1);
	ft_strlcat(filename, ".txt", ft_strlen(filename) + 5);
	free(nb);
	return (filename);
}

void	add_new_node_filename(t_lexer **head, int nb_hd)
{
	t_lexer	*dless;
	t_lexer	*new_node;
	t_lexer	*next;
	t_lexer	*current;

	new_node = malloc(sizeof(t_lexer));
	dless = dless_node(*head);
	while (dless && dless->next && dless->next->tok_type == T_SPACE)
		dless = dless->next;
	current = dless->next;
	new_node->tok_type = T_SENTENCE;
	new_node->str = create_filename(nb_hd);
	while (current && check_delim_char(current))
	{
		next = current->next;
		del_node(head, current);
		current = next;
	}
	if (dless->next)
		dless->next->prev = new_node;
	new_node->next = dless->next;
	new_node->prev = dless;
	dless->next = new_node;
}
