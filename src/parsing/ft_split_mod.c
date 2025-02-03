/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:36:51 by oloncle           #+#    #+#             */
/*   Updated: 2025/01/31 11:14:24 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static void	boucle_while(char si, char *c, int *new_word, int *count)
{
	int	j;

	j = 0;
	while (c[j])
	{
		if (si == c[j] && (*new_word) == 1)
		{
			*new_word = 0;
			(*count)++;
		}
		if (si != c[j] && *new_word == 0)
			*new_word = 1;
		j++;
	}
}

int	start_i(char const *s, char *c)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (c[j])
	{
		if (((char *)s)[i] == c[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (i);
}

void	end_var(char const *s, char *c, int *end)
{
	int	j;

	j = 0;
	while (c[j])
	{
		if (((char *)s)[*end] == c[j])
		{
			j = 0;
			(*end)--;
		}
		else
			j++;
	}
}

static int	nb_words(char const *s, char *c)
{
	int	count;
	int	i;
	int	new_word;
	int	end;

	new_word = 0;
	count = 1;
	i = start_i(s, c);
	end = ft_strlen((char *)s) - 1;
	if ((((char *)s)[i] == '\0') || i >= end)
		return (0);
	end_var(s, c, &end);
	while (((char *)s)[i] != '\0' && i <= end)
	{
		boucle_while(((char *)s)[i], c, &new_word, &count);
		i++;
	}
	return (count);
}

int	is_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	len_word(char const *s, char *c)
{
	int	i;

	i = 0;
	while (((char *)s)[i] && !(is_in_str(((char *)s)[i], c)))
		i++;
	return (i);
}

static char	*mot_split(char *str, char *c)
{
	char	*mot;
	int		i;
	int		j;

	mot = malloc(sizeof(char) * (1 + len_word(str, c)));
	if (!mot)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (c[j])
		{
			mot[i] = str[i];
			j++;
		}
		i++;
	}
	mot[i] = '\0';
	return (mot);
}

char	**ft_split(char const *s, char *c)
{
	char	**res;
	int		i;
	int		nb_word;

	nb_word = 0;
	i = 0;
	res = malloc(sizeof(char *) * (1 + nb_words((char *)s, c)));
	if (res == NULL)
		return (NULL);
	while (is_in_str(((char *)s)[i], c))
		i++;
	while (nb_word < (nb_words((char *)s, c)))
	{
		res[nb_word] = mot_split((char *)(s + i), c);
		if (res[nb_word] == NULL)
			return (NULL);
		i = i + len_word((char *)(s + i), c);
		while (is_in_str(((char *)s)[i], c))
			i++;
		nb_word++;
	}
	res[nb_word] = NULL;
	return (res);
}
