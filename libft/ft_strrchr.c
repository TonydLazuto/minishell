/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 08:59:09 by jdidier           #+#    #+#             */
/*   Updated: 2021/11/14 16:46:25 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		index;

	tmp = (char *)s;
	index = (int)ft_strlen(s);
	tmp += index;
	while (index >= 0 && *tmp != c)
	{
		tmp--;
		index--;
	}
	if (*tmp == c)
		return (tmp);
	else
		return (NULL);
}
