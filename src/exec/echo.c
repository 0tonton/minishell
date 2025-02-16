/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:53:01 by klabaune          #+#    #+#             */
/*   Updated: 2025/02/09 12:11:29 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

int	check_flag_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] && arg[i] == 'n')
			i++;
		if (!arg[i] && arg[i - 1] == 'n')
			return (1);
	}
	return (0);
}

int	ft_echo(char **arg)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (arg[i] && check_flag_n(arg[i]) == 1)
	{
		i++;
		new_line = -1;
	}
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
	return (0);
}
