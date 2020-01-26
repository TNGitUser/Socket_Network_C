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
		activity = select(max_sd + 1, &node->con_set, NULL, NULL, NULL);
		if (activity < 0) // be careful activity < 0 means that no fd is ready
			printf("Select Error");
		if (FD_ISSET(node->socket_fd, &node->con_set))
			manage_con_new(node);
		if (node->action != ACTION_IDLE)
			printf("Idle\n");
		else
			printf("Action : %i\n", node->action);
		//manage_con_event(node);
	}
	pthread_exit(NULL);
	return (NULL);
}

void		server_run(t_node *node)
{
	pthread_t	secretary;
	char		*server_cmd;

	if ((pthread_create(&secretary, NULL, server_loop, (void *)node)))
		error("Thead launch failed. Please retart server");
	while (get_next_line(STDIN_FILENO, &server_cmd) > 0)
	{
		server_dispatch(node, server_cmd);
		ft_memdel((void **)&server_cmd);
	}
	ft_memdel((void **)&server_cmd);
}
