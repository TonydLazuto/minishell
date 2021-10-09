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
					printf("node->cmd.arg : %s\n", node->cmd.arg[i]);
					i++;
				}
			}
			printf("node->type : %d\n", node->cmd.type);
			if (node->right)
				printf("\n");
		}
		node = node->right;
	}
}

void	ft_exit(t_node *node, const char *err, int check_exec)
{
	ft_putstr(err);
	if (check_exec)
		ft_putstr(node->cmd.arg[0]);
	ft_putstr("\n");
	while (node->parent)
		node = node->parent;
	clear_nodes(&node);
	exit(EXIT_FAILURE);
}