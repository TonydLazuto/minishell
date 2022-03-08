/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 11:47:30 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:22:03 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;
	unsigned char	tmpc;

	i = 0;
	tmpdest = (unsigned char *)dest;
	tmpsrc = (unsigned char *)src;
	tmpc = (unsigned char)c;
	while (i < n)
	{
		tmpdest[i] = tmpsrc[i];
		if (tmpsrc[i] == tmpc)
			return (&tmpdest[i + 1]);
		i++;
	}
	return (NULL);
}
