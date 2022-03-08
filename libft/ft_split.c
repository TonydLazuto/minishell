/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 10:35:38 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:21:09 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordscounter(char const *s, char c)
{
	int	flag;
	int	result;

	flag = 0;
	result = 0;
	while (*s)
	{
		if (*s != c && !flag)
		{
			flag = 1;
			result++;
		}
		if (*s == c)
			flag = 0;
		s++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	start;
	unsigned int	index;
	unsigned int	i;

	start = 0;
	index = 0;
	i = 0;
	result = malloc(sizeof(char *) * (ft_wordscounter(s, c) + 1));
	if (!result)
		return (NULL);
	while (s[index])
	{
		if (index > 0 && s[index] != c && s[index - 1] == c)
			start = index;
		if (index > 0 && s[index] == c && s[index - 1] != c)
			result[i++] = ft_substr(s, start, (index - start));
		index++;
	}
	if (index > 0 && s[index - 1] != c)
		result[i++] = ft_substr(s, start, (index - start));
	result[i] = NULL;
	return (result);
}
