/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:19:23 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 19:36:38 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;

	i = 0;
	if (n == 0)
		return (0);
	str = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str == *str2 && ++i < n)
	{
		str++;
		str2++;
	}
	return ((int)(*str - *str2));
}
