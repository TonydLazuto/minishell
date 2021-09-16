/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:20:10 by aderose           #+#    #+#             */
/*   Updated: 2020/05/02 23:06:20 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*s_dst;
	unsigned char	*s_src;

	i = 0;
	s_dst = (unsigned char *)dst;
	s_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (s_src < s_dst)
		while (++i <= len)
			s_dst[len - i] = s_src[len - i];
	else
		while (len-- > 0)
			*(s_dst++) = *(s_src++);
	return (dst);
}
