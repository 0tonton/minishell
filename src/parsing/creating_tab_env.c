/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_tab_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:58:07 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 11:49:55 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	len_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*increment_shlvl(char *var)
{
	int	len;
	char	*new_var;
	char	*str_nb;

	len = len_var(var);
	new_var = NULL;
	if (len == 5 && !ft_strncmp(var, "SHLVL", len))
	{
		str_nb = ft_itoa(ft_atoi(var + len + 1) + 1);
		new_var = ft_calloc(8 + ft_strlen(str_nb), sizeof(char));
		ft_strlcat(new_var, "SHLVL=", 7);
		ft_strlcat(new_var, str_nb, ft_strlen(new_var) + ft_strlen(str_nb) + 1);
		free(str_nb);
	}
	return (new_var);
}

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
	char	*temp_var;
	int	i;

	i = 0;
	var = og_env[i];
	tab_var = malloc(sizeof(char **) * (nb_var(og_env) + 1));
	while (var)
	{
		temp_var = increment_shlvl(var);
		if (temp_var)
			var = temp_var;
		tab_var[i] = var;
		i++;
		var = og_env[i];
	}
	tab_var[i] = NULL;
	return(tab_var);
}
