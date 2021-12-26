/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 11:37:24 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:14:14 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	i = 0;
	result = malloc(sizeof(*result) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		result[i] = f(i, *s);
		s++;
		i++;
	}
	result[i] = '\0';
	return (result);
}
