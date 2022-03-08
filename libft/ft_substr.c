/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:37:51 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 09:40:33 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	if (ft_strlen(s) <= start)
		len = 0;
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len && s[i])
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}
