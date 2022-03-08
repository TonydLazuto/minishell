/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:00:39 by jdidier           #+#    #+#             */
/*   Updated: 2021/12/29 19:22:25 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(char *delemiter, char *file)
{
	int		ret;
	int		fd;
	char	buf[4096];
	char	*delemitern;

	delemitern = ft_strjoin(delemiter, "\n");
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
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

char	*set_file(int i)
{
	char	*tmp;
	char	*result;

	tmp = ft_itoa(i);
	result = ft_strjoin("/tmp/", tmp);
	free(tmp);
	return (result);
}

void	get_heredoc(t_list *node)
{
	t_token		*tk;
	t_token		*tk_next;
	char		*tmp;
	char		*file;
	static int	i;

	i = 1;
	while (node)
	{
		tk = (t_token *)node->content;
		tk_next = get_next_token(node);
		if (tk->type == TK_HERE_DOC)
		{
			file = set_file(i);
			heredoc(tk->value, file);
			tmp = tk->value;
			tk->value = file;
			free(tmp);
		}
		if (tk_next && tk_next->type != TK_HERE_DOC)
			i++;
		node = node->next;
	}
}
