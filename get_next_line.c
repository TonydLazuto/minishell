/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderose <aderose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:05:16 by aderose           #+#    #+#             */
/*   Updated: 2021/09/06 16:46:04 by aderose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pos_new_line(char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

static int	check_error(int fd, char **cur, char **line)
{
	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!*cur)
	{
		*cur = (char *)malloc(BUFFER_SIZE + 1);
		if (!*cur)
			return (-1);
		*cur[0] = '\0';
	}
	return (0);
}

static char	*split_lines(char **line, char *cur, int pos)
{
	char	*tmp;

	tmp = NULL;
	*line = my_substr(cur, 0, pos);
	if (!*line)
		return (NULL);
	tmp = my_substr(cur, pos + 1, my_strlen(cur) - pos + 1);
	if (!tmp)
		return (NULL);
	my_free(&cur);
	cur = my_strdup(tmp);
	if (!cur)
		return (NULL);
	my_free(&tmp);
	return (cur);
}

static char	*read_buf(int fd, char *cur, int *ret, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		pos;

	pos = pos_new_line(cur);
	if (read(fd, buf, 0) < 0)
		return (NULL);
	*ret = 1;
	while (pos == -1 && *ret > 0)
	{
		*ret = read(fd, buf, BUFFER_SIZE);
		buf[*ret] = '\0';
		cur = strjoinfree(cur, buf);
		if (!cur)
			return (NULL);
		pos = pos_new_line(cur);
	}
	if (pos != -1)
	{
		cur = split_lines(line, cur, pos);
		if (!cur)
			return (NULL);
	}
	if (*ret > 0)
		*ret = 1;
	return (cur);
}

int	get_next_line(int fd, char **line)
{
	static char	*cur = NULL;
	int			ret;

	ret = 1;
	if (check_error(fd, &cur, line) == -1)
		return (-1);
	cur = read_buf(fd, cur, &ret, line);
	if (!cur)
		return (-1);
	if (ret == 0)
	{
		if (cur)
		{
			*line = my_strdup(cur);
			my_free(&cur);
		}
		else
			*line = my_strdup("\0");
	}
	return (ret);
}
