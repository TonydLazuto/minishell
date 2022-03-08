/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 13:46:03 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:22:32 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmpdest;
	unsigned char	*tmpsrc;

	i = 0;
	if (!src && !dest)
		return (dest);
	tmpdest = (unsigned char *)dest;
	tmpsrc = (unsigned char *)src;
	while (i < n)
	{
		*tmpdest = *tmpsrc;
		tmpdest++;
		tmpsrc++;
		i++;
	}
	return (dest);
}
