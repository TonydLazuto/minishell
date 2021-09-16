/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:34:19 by aderose           #+#    #+#             */
/*   Updated: 2020/05/15 16:32:51 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	check_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	while (check_set(set, s[i]))
		i++;
	while (check_set(set, s[j]) && j)
		j--;
	len = j - i + 1;
	if (len < 0)
		len = 0;
	str = ft_substr(s, i, len);
	if (!str)
		return (NULL);
	return (str);
}
