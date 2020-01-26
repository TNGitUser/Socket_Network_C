#include "socket.h"

static void	loop(t_node *node)
{
	if (node->type == SERVER)
		server_run(node);
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
