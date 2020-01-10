
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
	char	buffer[BUFFER_SIZE + 1];

	if (node->type == SERVER)
		server_loop(node);
	else
	{
		printf("Awaiting input\n");
		bzero(buffer, BUFFER_SIZE);
		printf("%i\n", strcmp(buffer, "START"));
		while (strcmp(buffer, "START"))
		{
			bzero(buffer, BUFFER_SIZE);
			read(node->socket_fd, buffer, BUFFER_SIZE);
		}
		printf("Input received\n");
		while (1)
		{
			time_t current_time;
			struct tm * time_info;
			char timeString[10];  // space for "HH:MM:SS\0"

			time(&current_time);
			time_info = localtime(&current_time);

			strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
			timeString[9] = '\0';
			//rsize = read(node->socket_fd, buf, BUFFER_SIZE);
			printf("Client : %s\n", timeString);
			send(node->socket_fd, timeString , strlen(timeString) , 0);
			sleep(5);
		}
	}
}

static void get_client_info(t_node *node)
{
	char	target[1024];
	char	ans[1024];

	bzero(target, 1024);
	printf("Please input target ip : ");
	//scanf("%ms", &target); // Only for linux because mac sucks for scanf
	scanf("%s", target);
	printf("Is %s correct ? (Y\\n) ", target);
	scanf("%s", ans);
	if (!strcmp(ans, "Y"))
		init_client(node, target);
	else
		get_client_info(node);
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
