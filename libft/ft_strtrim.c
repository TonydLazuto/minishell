/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:54:36 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:13:07 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char c, char const *charset)
{
	unsigned int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*result;
	unsigned int	start;
	unsigned int	end;
	int				result_len;

	start = 0;
	if (*s1 == '\0')
		return (ft_substr(s1, 0, 0));
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_ischarset(s1[start], set))
		start++;
	while (end && ft_ischarset(s1[end], set))
		end--;
	if ((int)(end - start + 1) >= 0)
		result_len = end - start + 1;
	else
		result_len = 0;
	result = ft_substr(s1, start, result_len);
	return (result);
}
