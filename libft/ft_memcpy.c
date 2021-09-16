/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:19:46 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 19:36:03 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char	*s_dst;
	unsigned char	*s_src;
	size_t			i;

	s_dst = (unsigned char *)dst;
	s_src = (unsigned char *)src;
	i = 0;
	if (!n || s_dst == s_src)
		return (s_dst);
	while (i < n)
	{
		s_dst[i] = s_src[i];
		i++;
	}
	return (s_dst);
}
