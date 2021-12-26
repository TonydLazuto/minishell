/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:00:39 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/15 14:13:58 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *delemiter)
{
	int		ret;
	int		fd;
	char	buf[4096];
	char	*delemitern;

	delemitern = ft_strjoin(delemiter, "\n");
	fd = open("/tmp/1", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(1, "> ", 2);
	ret = read(0, buf, 4096);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (!ft_strcmp(delemitern, buf))
			break ;
		ft_putstr_fd(buf, fd);
		write(1, "> ", 2);
		ret = read(0, buf, 4096);
	}
	free(delemitern);
	close(fd);
}

void	get_heredoc(t_list *node)
{
	t_token	*tk;
	char	*tmp;

	while (node)
	{
		tk = (t_token *)node->content;
		if (tk->type == TK_HERE_DOC)
		{
			heredoc(tk->value);
			tmp = tk->value;
			tk->value = ft_strdup("/tmp/1");
			free(tmp);
		}
		node = node->next;
	}
}
