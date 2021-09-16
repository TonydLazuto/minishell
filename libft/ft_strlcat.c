/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:31:19 by aderose           #+#    #+#             */
/*   Updated: 2020/05/02 18:32:16 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst,
			const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	dst_len;

	if (dstsize > 65535)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	dst_len = i;
	len = i + ft_strlen(src);
	j = 0;
	while (i < len && i < (dstsize - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (dstsize < dst_len)
		return (dstsize + ft_strlen(src));
	return (len);
}
