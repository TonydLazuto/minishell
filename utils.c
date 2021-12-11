/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:14:16 by aderose           #+#    #+#             */
/*   Updated: 2021/11/20 13:14:21 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_strncmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			n;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (ft_strlen(s1) <= ft_strlen(s2))
		n = ft_strlen(s1);
	else
		n = ft_strlen(s2);
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n - 1)
		i++;
	if (str1[i] != str2[i])
	{
		if (str1[i] - str2[i] > 0)
			return (1);
		else
			return (-1);
	}
	return (0);
}

char	*strjoinfree(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
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
	ft_free(&s1);
	return (str);
}

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

void	ft_error(t_node *node, char *err)
{
	ft_putstr_fd(err, 1);
	ft_putstr_fd("\n", 1);
	while (node->back)
		node = node->back;
	clearnodes(&node);
	exit(EXIT_FAILURE);
}
