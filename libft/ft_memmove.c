/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 14:14:16 by jdidier           #+#    #+#             */
/*   Updated: 2020/05/12 17:49:42 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;
	size_t			i;

	tmpdst = (unsigned char *)dst;
	tmpsrc = (unsigned char *)src;
	if (!(tmpdst || tmpsrc))
		return (dst);
	i = len;
	if ((tmpdst > tmpsrc) && (tmpdst < tmpsrc + len))
		while (i-- > 0)
			*(tmpdst + i) = *(tmpsrc + i);
	else
		while (i-- > 0)
			*tmpdst++ = *tmpsrc++;
	return (dst);
}
