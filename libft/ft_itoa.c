/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 15:20:39 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:26:34 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(int n, char *result, int *i)
{
	long int	nbl;

	nbl = n;
	if (nbl < 0)
	{
		result[*i] = '-';
		nbl *= -1;
		*i += 1;
	}
	if (nbl >= 10)
	{
		ft_recursive(nbl / 10, result, i);
		ft_recursive(nbl % 10, result, i);
	}
	else
	{
		result[*i] = (nbl + '0');
		*i += 1;
	}
}

char	*ft_itoa(int n)
{
	int		counter;
	int		nb;
	char	*result;

	counter = 0;
	nb = n;
	if (nb < 0)
	{
		counter++;
		nb *= -1;
	}
	while (nb >= 1)
	{
		nb /= 10;
		counter++;
	}
	result = malloc(sizeof(*result) * (counter + 1));
	if (!result)
		return (NULL);
	counter = 0;
	ft_recursive(n, result, &counter);
	result[counter] = '\0';
	return (result);
}
