/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:13:17 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
	{
		printf("%s\n", path);
		return (0);
	}
	perror("pwd");
	return (1);
}
