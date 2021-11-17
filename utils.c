#include "minishell_bis.h"

void	printnodes(t_astnode *mynode)
{
	t_astnode	*node;
	int		i;

	node = mynode;
	while (node)
	{
		i = 0;
		if (node->cmd.arg)
		{
			while (node->cmd.arg[i])
			{
				printf("node->cmd.arg : %s\n", node->cmd.arg[i]);
				i++;
			}
		}
		printf("node->type : %d\n", node->type);
		if (node->right)
			printf("\n");
		node = node->right;
	}
}

int	ft_strcmp(char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] != str2[i])
		return (-1);
	return (0);
}


void	ft_exit(t_astnode *node, char *err)
{
	ft_putstr_fd(err, 1);
	ft_putstr_fd("\n", 1);
	while (node->parent)
		node = node->parent;
	clearnodes(&node);
	exit(EXIT_FAILURE);
}
