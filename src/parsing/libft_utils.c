/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:14:27 by oloncle           #+#    #+#             */
/*   Updated: 2025/01/30 13:06:05 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms.h"
#include "../../inc/lexing.h"

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;

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
	while (str[i] && !ft_is_space(str[i]) && !is_special(str[i]))
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

