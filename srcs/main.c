#include "socket.h"

static void server_init_msg(t_node *node)
{
	char ip[INET_ADDRSTRLEN];

	printf("Server initialized -\n");
	inet_ntop(AF_INET, &(node->serv_addr.sin_addr), ip, INET_ADDRSTRLEN);
	printf("Server IP          : %s\nServer PORT        : %i\n", ip, PORT);
	printf("Server max client  : %i\n", MAXCON);
}

static void server_loop(t_node *node)
{
	int	max_sd;
	int	activity;

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
		manage_con_event(node);
	}
}

static void	loop(t_node *node)
{
	if (node->type == SERVER)
		server_loop(node);
	else
	{
		while (node->info.active)
		{
			await_command(node);
		}
	}
}

static void get_client_info(t_node *node)
{
	char	target[1024];

	bzero(target, 1024);
	printf("Please input target ip : ");
	scanf("%s", target);
	if (is_ip_valid(target))
		init_client(node, target);
	else
	{
		printf("\033[0;31mError, IP is invalid\033[0m\n");
		get_client_info(node);
	}
}

int			main(int argc, char **argv)
{
	t_node	node;

	if (argc != 2)
		error("usage : ./cluster [server | client]");
	if (strcmp(argv[1], "server") && strcmp(argv[1], "client"))
		error("cluster : Error unknown protocol");
	if (!strcmp(argv[1], "server"))
		init_server(&node);
	else if (!strcmp(argv[1], "client"))
		get_client_info(&node);
	loop(&node);
}
