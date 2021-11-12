#include "minishell_bis.h"

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


void	ft_exit(t_cmd *cmd, char *err)
{
	ft_putstr_fd(err, 1);
	ft_putstr_fd("\n", 1);
	while (cmd->back)
		cmd = cmd->back;
	clearcmds(&cmd);
	exit(EXIT_FAILURE);
}
