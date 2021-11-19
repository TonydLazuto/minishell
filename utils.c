#include "minishell.h"

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

void	ft_error(t_astnode *node, char *err)
{
	ft_putstr_fd(err, 1);
	ft_putstr_fd("\n", 1);
	while (node->parent)
		node = node->parent;
	clearnodes(&node);
	exit(EXIT_FAILURE);
}

int		my_strncmp(char *s1, char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			n;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (ft_strlen(s1) <= ft_strlen(s2))
		n = ft_strlen(s1);
	else
		n = ft_strlen(s2);
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n - 1)
		i++;
	if (str1[i] != str2[i])
	{
		if (str1[i] - str2[i] > 0)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int		is_builtin(t_astnode *node)
{
	if (!node->cmd.arg[0])
		return (0);
	if (my_strncmp(node->cmd.arg[0], "cd") == 0
		|| my_strncmp(node->cmd.arg[0], "echo") == 0
		|| my_strncmp(node->cmd.arg[0], "pwd") == 0
		|| my_strncmp(node->cmd.arg[0], "env") == 0
		|| my_strncmp(node->cmd.arg[0], "export") == 0
		|| my_strncmp(node->cmd.arg[0], "unset") == 0
		|| my_strncmp(node->cmd.arg[0], "exit") == 0)
		return (1);
	return (0);
}