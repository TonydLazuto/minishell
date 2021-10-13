#include "minishell.h"

void	printnodes(t_node *mynode)
{
	t_node	*node;

	node = mynode;
	while (node)
	{
		printcmds(node->cmd);
		node = node->next;
	}
}


void	printcmds(t_cmd *mycmd)
{
	t_cmd	*cmd;
	int		i;

	cmd = mycmd;
	while (cmd)
	{
		i = 0;
		if (cmd->arg)
		{
			while (cmd->arg[i])
			{
				printf("cmd->arg : %s\n", cmd->arg[i]);
				i++;
			}
		}
		printf("cmd->type : %d\n", cmd->type);
		if (cmd->next)
			printf("\n");
		cmd = cmd->next;
	}
}


void	ft_exit(t_node *node, char *err)
{
	ft_putstr_fd(err, 1);
	ft_putstr_fd("\n", 1);
	while (node->back)
		node = node->back;
	clearnodes(node);
	exit(EXIT_FAILURE);
}
