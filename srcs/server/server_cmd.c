
#include "socket.h"

static int	cmd_is_srv_cmd(char *cmd)
{
	int					i;
	static const char	*directives[] = { "SET", "STATUS", "RUN", "LOCK"
		, "UNLOCK", NULL};

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
	printf("Lock Status : %s\033[0m\n", node->lock ? "\033[32mON"
			: "\033[31mOFF");
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

static int	server_runn(t_node *node)
{
	char	target[1024];
	char	*data;
	int		i;
	char	*cmd;

	if (!node->lock)
		printf("Server need to be LOCK to use RUN");
	if (!server_get_ready(node))
		return (nerror("No client are ready ! Aborting..."));
	printf("Input target : ");
	scanf("%s", target);
	data = get_data_filename(target);
	i = 0;
	cmd = get_other_cmd(SEND_SCENE, node);
	while (i < MAXCON)
	{
		if (node->clients[i].active)
		{
			server_to_client(node, i, cmd, SEND_SCENE);
			send_file(data, node, node->clients[i].socket);
		}
		++i;
	}
	ft_memdel((void **)&data);
	return (0);
}

/*
**	Function will be used to set workload of each child
*/

static int	server_set(t_node *node)
{
	int		act;
	int		wl[2][2];
	int		bds[4];
	int		i[2];
	char	*cmd_bds;

	if (!node->lock)
		return (nerror("Server need to be LOCK to use SET"));
	if ((act = server_get_active(node)) <= 0)
		return (nerror("No client. Aborting operation..."));
	server_get_workload(node, act, wl[0], wl[1]);
	i[1] = 0;
	i[0] = -1;
	bds[0] = 0;
	bds[1] = EX_WIDTH;
	act = server_get_active(node);
	while (++i[0] < MAXCON)
		if (node->clients[i[0]].active)
		{
			bds[2] = wl[0][1] * i[1];
			bds[3] = wl[0][1] * (i[1] + 1) + (i[1] + 1 == act ? wl[1][1] : 0);
			cmd_bds = get_set_cmd(1, node->clients[i[0]], bds);
			server_to_client(node, i[0], cmd_bds, SET_BOUNDS);
			node->clients[i[0]].ready = 1;
			ft_memdel((void **)&cmd_bds);
			++i[1];
		}
	return (0);
}

int			server_dispatch(t_node *node, char *cmd)
{
	int	cmd_t;

	if ((cmd_t = cmd_is_srv_cmd(cmd)) == -1 || cmd_t > 4)
		return (nerror("Unknown server command : use [SET, STATUS, RUN\
, LOCK, UNLOCK]"));
	if (cmd_t == 0)
		return (server_set(node));
	else if (cmd_t == 1)
		return (server_status(node, cmd));
	else if (cmd_t == 2)
		return (server_runn(node));
	else if (cmd_t == 3 || cmd_t == 4)
		node->lock = cmd_t == 3 ? 1 : 0;
	return (0);
}
