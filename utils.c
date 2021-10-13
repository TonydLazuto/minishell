#include "minishell.h"

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


void	ft_exit(t_cmd *cmd, char *err)
{
	ft_putstr_fd(err, 1);
	ft_putstr_fd("\n", 1);
	while (cmd->back)
		cmd = cmd->back;
	clearcmds(&cmd);
	exit(EXIT_FAILURE);
}
