/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:25:09 by aderose           #+#    #+#             */
/*   Updated: 2021/05/01 07:10:19 by tonyd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**fillstr(char *s, char c, char **str)
{
	unsigned int	i;
	unsigned int	start;
	size_t			len;
	int				wrd;

	i = 0;
	start = 0;
	len = 0;
	wrd = -1;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (len != 0)
				str[++wrd] = ft_substr(s, start, len);
			start = i + 1;
			len = -1;
		}
		i++;
		len++;
	}
	if (len != 0)
		str[++wrd] = ft_substr(s, start, len);
	str[++wrd] = NULL;
	return (str);
}

static size_t	get_nbwords(char *s, char c)
{
	size_t	i;
	int		j;
	size_t	words;

	i = 0;
	j = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (j != 0)
				words++;
			j = -1;
		}
		i++;
		j++;
	}
	if (j != 0)
		words++;
	return (words);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	size_t	words;

	str = NULL;
	if (!s || !c)
		return (NULL);
	words = get_nbwords(s, c);
	if (words == 0)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	str = fillstr(s, c, str);
	return (str);
}
