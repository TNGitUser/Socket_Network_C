
#include "socket.h"

static int	cmd_is_srv_cmd(char *cmd)
{
	int					i;
	static const char	*directives[] = { "SET", "STATUS", "RUN", NULL};

	i = 0;
	while (directives[i])
	{
		if (!ft_strncmp(cmd, directives[i], ft_strlen(directives[i])))
		{
			return (i);
		}
		++i;
	}
	return (-1);
}

static int	server_status(t_node *node, char *cmd)
{
	int	i;

	if (!(cmd = ft_strstr(cmd, "STATUS")) || *(cmd + 6) != '\0')
		return (nerror("Error, STATUS command is not correctly formated.\
 Expecting 'STATUS'"));
	i = 0;
	while (i < MAXCON)
	{
		if (node->clients[i].active)
			printf("Client %i : [%s] \033[32mActive\033[0m, socket : %i\n"
					, i, node->clients[i].name, node->clients[i].socket);
		else
			printf("Client %i : \033[31mInactive\033[0m\n", i);
		++i;
	}
	return (0);
}

static int	server_runn(t_node *node, char *cmd)
{
	printf("Not implemented yet\n");
	return (0);
}

static int	server_set(t_node *node, char *cmd)
{
	printf("Not implemented yet\n");
	return (0);
}

int			server_dispatch(t_node *node, char *cmd)
{
	int	cmd_t;

	if ((cmd_t = cmd_is_srv_cmd(cmd)) == -1 || cmd_t > 2)
		return (nerror("Unknown server command : use [SET, STATUS, RUN]"));
	if (cmd_t == 0)
		return (server_set(node, cmd));
	else if (cmd_t == 1)
		return (server_status(node, cmd));
	else if (cmd_t == 2)
		return (server_runn(node, cmd));
	return (0);
}
