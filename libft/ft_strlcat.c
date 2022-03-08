/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 17:40:39 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:15:03 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (*dst)
		dst++;
	while (*src && (i + dst_len < (size - 1)))
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = '\0';
	if (size < dst_len)
		return (size + src_len);
	return (src_len + dst_len);
}
