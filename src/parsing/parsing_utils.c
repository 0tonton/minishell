/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:10:56 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/12 17:13:25 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	count_cmd(t_node *head_node)
{
	t_node	*current;
	int	i;

	i = 0;
	current = head_node;
	while (current->type == 1)
	{
		i++;
		current = ((t_pipe_node *)current)->left;
	}
	return (i + 1);
}