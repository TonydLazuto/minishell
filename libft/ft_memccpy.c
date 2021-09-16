/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:18:12 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 19:35:31 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
			int c, size_t n)
{
	size_t			i;
	unsigned char	*s_dst;
	unsigned char	*s_src;

	s_dst = (unsigned char *)dst;
	s_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		s_dst[i] = s_src[i];
		if (s_src[i] == (unsigned char)c)
			return ((void *)(s_dst + i + 1));
		i++;
	}
	return (NULL);
}
