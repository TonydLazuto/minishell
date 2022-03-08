/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:03:08 by jdidier           #+#    #+#             */
/*   Updated: 2021/10/14 10:06:16 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_malloc(void *target, size_t size)
{
	target = malloc(sizeof(*target) * size);
	if (!target)
		return (0);
	else
		return (1);
}
