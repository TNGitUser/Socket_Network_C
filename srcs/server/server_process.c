#include "socket.h"

static void server_init_msg(t_node *node)
{
	char ip[INET_ADDRSTRLEN];

	printf("Server initialized -\n");
	inet_ntop(AF_INET, &(node->serv_addr.sin_addr), ip, INET_ADDRSTRLEN);
	printf("Server IP          : %s\nServer PORT        : %i\n", ip, PORT);
	printf("Server max client  : %i\n", MAXCON);
}

static void *server_loop(void *vnode)
{
	t_node *node;
	int		max_sd;
	int		activity;

	node = (t_node *)vnode;
	server_init_msg(node);
	while (1)
	{
		FD_ZERO(&(node->con_set));
		FD_SET(node->socket_fd, &(node->con_set));
		max_sd = node->socket_fd;

		set_add_child(node, &max_sd);
		printf("Waiting for select\n");
		activity = select(max_sd + 1, &node->con_set, NULL, NULL, NULL);
		printf("Wait ended\n");
		if (activity < 0) // be careful activity < 0 means that no fd is ready
			printf("Select Error");
		if (FD_ISSET(node->socket_fd, &node->con_set))
			manage_con_new(node);
		manage_con_event(node);
	}
	pthread_exit(NULL);
	return (NULL);
}
/*
static void	*server_actions(void *vnode)
{
	t_node *node;
	int		old_act;
	int		i;
	char	*cmd;
	int		work[4];
	
	node = (t_node *)vnode;
	old_act = -2;
	while (1)
	{
		if (node->action != old_act)
		{
			printf("Current action : %i\n", node->action);
			old_act = node->action;
			if (node->action == ACTION_BOUNDS)
			{
				i = 0;
				work[0] = 0;
				work[1] = EX_WIDTH;
				while (i < MAXCON)
				{
					if (node->clients[i].active)
					{
						work[2] = node->work[0] * i + align;
						work[3] = node->work[0] * (i + 1) + node->work[3];
						node->work[3] = 0;
						cmd = get_set_cmd(1, node->clients[i], work);
						server_to_client(node, i, cmd, SET_BOUNDS);
					}
					++i;
				}
			}
			node->action = ACTION_IDLE;
		}
	}
	pthread_exit(NULL);
	return (NULL);
}*/

void		server_run(t_node *node)
{
	pthread_t	secretary[2];
	char		*server_cmd;

	if ((pthread_create(&secretary[0], NULL, server_loop, (void *)node)))
		error("Thead launch failed. Please restart server");
/*	if ((pthread_create(&secretary[1], NULL, server_actions, (void *)node)))
		error("Thead launch failed. Please restart server");*/
	while (get_next_line(STDIN_FILENO, &server_cmd) > 0)
	{
		server_dispatch(node, server_cmd);
		ft_memdel((void **)&server_cmd);
	}
	ft_memdel((void **)&server_cmd);
}
