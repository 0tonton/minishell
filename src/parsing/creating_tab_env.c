/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:58:07 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/05 10:08:41 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	nb_var(char **env)
{
	int	i;
	char	*var;

	i = 0;
	var = env[0];
	while (var)
	{
		i++;
		var = env[i];
	}
	return (i);
}

char	**tab_var_env(char **og_env)
{
	char	**tab_var;
	char	*var;
	int	i;

	i = 0;
	var = og_env[i];
	tab_var = malloc(sizeof(char **) * (nb_var(og_env) + 1));
	while (var)
	{
		tab_var[i] = var;
		i++;
		var = og_env[i];
	}
	tab_var[i] = NULL;
	return(tab_var);
}