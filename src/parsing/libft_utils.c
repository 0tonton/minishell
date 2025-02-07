/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:14:27 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:43:14 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	dup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		dup[i] = ((char *)s)[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_len_word(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && !ft_is_space(str[i]) && !is_special(str[i]))
		i++;
	return (i);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	lendst;

	lendst = ft_strlen(dst);
	
	i = 0;
	if (size <= lendst)
		return (ft_strlen(src) + size);
	while (i < (size - lendst - 1) && ((char *)src)[i] != '\0')
	{
		dst[lendst + i] = ((char *)src)[i];
		i++;
	}
	if (size >= (ft_strlen(src) + lendst) || lendst < size)
		dst[lendst + i] = '\0';
	return (lendst + ft_strlen(src));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	int		n;
	int	i;

	i = 0;
	n = nmemb * size;
	result = malloc(n);
	if (!(result))
		return (NULL);
	while (i < n)
	{
		((char *)result)[i] = 0;
		i++;
	}
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				diff;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s2 || !s1)
		return (-1);
	n--;
	while (((char *)s1)[i] != '\0' &&
	((char *)s1)[i] == ((char *)s2)[i] && i < n)
		i++;
	diff = ((char *)s1)[i] - ((char *)s2)[i];
	if (((char *)s1)[i] < 0 || ((char *)s2)[i] < 0)
		diff = -diff;
	return (diff);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	minus;

	i = 0;
	nb = 0;
	minus = 1;
	while (((char *)nptr)[i] && ((((char *)nptr)[i] >= 9
	&& ((char *)nptr)[i] <= 13) || ((char *)nptr)[i] == 32))
		i++;
	if (((char *)nptr)[i] && (((char *)nptr)[i] == '-'
	|| ((char *)nptr)[i] == '+'))
	{
		if (((char *)nptr)[i] == '-')
			minus = -minus;
		i++;
	}
	while (((char *)nptr)[i] >= '0' && ((char *)nptr)[i] <= '9'
	&& ((char *)nptr)[i])
	{
		nb = nb * 10 + (((char *)nptr)[i] - '0');
		i++;
	}
	return (minus * nb);
}
