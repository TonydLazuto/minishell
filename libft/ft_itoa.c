/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:14:44 by aderose           #+#    #+#             */
/*   Updated: 2020/05/12 18:47:55 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	set_size(int n)
{
	size_t	size;

	size = 1;
	if (n < 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*s;
	size_t	size;

	nb = (long)n;
	size = set_size(n);
	s = ft_strnew(size);
	if (!s)
		return (NULL);
	if (nb == 0)
		s[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		s[0] = '-';
	}
	while (nb > 0)
	{
		size--;
		s[size] = nb % 10 + '0';
		nb /= 10;
	}
	return (s);
}
