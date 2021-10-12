/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:06:23 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 16:48:15 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_free(char **s)
{
	free(*s);
	*s = NULL;
}

size_t	my_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

char	*my_strdup(char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(my_strlen(s1) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (i < my_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*strjoinfree(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1)
	{
		str = my_substr(s2, 0, my_strlen(s2));
		if (!str)
			return (NULL);
		return (str);
	}
	str = (char *)malloc(my_strlen(s1) + my_strlen(s2) + 1);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i] = *s2++;
		i++;
	}
	str[i] = '\0';
	my_free(&s1);
	return (str);
}

char	*my_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= my_strlen(s))
		len = 0;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[i + start] != '\0')
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}
