/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:15:38 by oloncle           #+#    #+#             */
/*   Updated: 2025/02/07 14:41:26 by oloncle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/lexing.h"
#include "../../../inc/ms.h"

static int	ft_power(int nb, int power)
{
	int	i;
	int	res;

	res = 1;
	i = 0;
	while (i < power)
	{
		res = res * nb;
		i++;
	}
	return (res);
}

static void	checking_minus_assign_dizaine(long int *long_n,
int *minus, int *i, int *dizaine)
{
	if (*long_n < 0)
	{
		(*minus)++;
		*long_n = -(*long_n);
		(*i)++;
	}
	while (*long_n / (ft_power(10, *dizaine)) > 9)
		(*dizaine)++;
}

char	*ft_itoa(int n)
{
	char		*res;
	long int	long_n;
	int			dizaine;
	int			minus;
	int			i;

	minus = 0;
	long_n = n;
	dizaine = 0;
	i = 0;
	checking_minus_assign_dizaine(&long_n, &minus, &i, &dizaine);
	res = malloc(sizeof(char) * (dizaine + minus + 2));
	if (!res)
		return (NULL);
	if (minus)
		res[0] = '-';
	while (dizaine >= 0)
	{
		res[i++] = '0' + long_n / ft_power(10, dizaine);
		long_n = long_n - (ft_power(10, dizaine)
				* (long_n / ft_power(10, dizaine)));
		dizaine--;
	}
	res[i] = '\0';
	return (res);
}
