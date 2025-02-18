/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:38:09 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/18 11:40:32 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/ms.h"

char	*assiging_new_str(char *temp, char *node_str)
{
	char	*new_str;

	if (node_str[2])
	{
		new_str = ft_calloc(ft_strlen(node_str + 1) + \
		ft_strlen(temp), sizeof(char));
		ft_strlcat(new_str, temp, ft_strlen(temp) + 1);
		ft_strlcat(new_str, node_str + 2, ft_strlen(new_str) + \
		ft_strlen(node_str + 1));
	}
	else
		new_str = ft_strdup(temp);
	return (new_str);
}
