/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:33:44 by aderose           #+#    #+#             */
/*   Updated: 2020/05/02 18:46:15 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		count;
	int		i;

	str = (char *)s;
	count = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count = i;
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	if (count == -1)
		return (NULL);
	return (&str[count]);
}
