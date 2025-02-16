/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:56:09 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/16 12:36:33 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

void	create_and_add_to_hdfile(char *buffer, int nb_hd)
{
	int		fd;
	char	*filename;

	if (buffer)
	{
		filename = create_filename(nb_hd);
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 00744);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		close(fd);
		free(filename);
	}
}

int	check_nb_hd(t_lexer *head)
{
	int		nb;
	t_lexer	*current;

	current = head;
	nb = 0;
	while (current)
	{
		if (current->tok_type == T_DLESS)
			nb++;
		current = current->next;
	}
	return (nb);
}

int	if_more_hd(int nb_hd, t_lexer **head)
{
	t_lexer	**pt_dless;
	int		ret_manage;

	ret_manage = 1;
	if (nb_hd > 1)
	{
		pt_dless = malloc(sizeof(t_lexer *));
		*pt_dless = dless_node(*head);
		if ((*pt_dless)->next)
		{
			(*pt_dless) = (*pt_dless)->next;
			ret_manage = manage_hd(pt_dless);
		}
		free(pt_dless);
	}
	return (ret_manage);
}

int	manage_hd(t_lexer **head)
{
	char	*delim;
	char	*buffer;
	int		nb_hd;

	delim = find_delim(*head);
	nb_hd = check_nb_hd(*head);
	if (!delim || !delim[0])
	{
		free(delim);
		return (0);
	}
	buffer = NULL;
	while (!buffer || ft_strncmp(delim, buffer, ft_strlen(delim)) \
	|| ft_strlen(delim) != ft_strlen(buffer))
	{
		create_and_add_to_hdfile(buffer, nb_hd);
		if (buffer)
			free(buffer);
		buffer = readline("> ");
	}
	if (buffer)
		free(buffer);
	free(delim);
	add_new_node_filename(head, nb_hd);
	return (if_more_hd(nb_hd, head));
}
