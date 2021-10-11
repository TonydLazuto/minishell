#include "minishell.h"

void	printnodes(t_node *mynode)
{
	t_node	*node;
	int		i;

	node = mynode;
	while (node)
	{
		printf("node->ntype : %d\n", node->ntype);
		if (node->ntype  == CMD)
		{
			i = 0;
			if (node->cmd.arg)
			{
				while (node->cmd.arg[i])
				{
					printf("node->cmd.arg[%d] : %s\n", i, node->cmd.arg[i]);
					i++;
				}
			}
			printf("node->cmd.type : %d\n", node->cmd.type);
			if (node->right)
				printf("\n");
		}
		node = node->right;
	}
}

void	ft_exit(t_node *node, char *err)
{
	ft_putstr_fd(err, 1);
	ft_putstr_fd("\n", 1);
	while (node->parent)
		node = node->parent;
	clear_node(node);
	exit(EXIT_FAILURE);
}