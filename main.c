
#include "socket.h"

static void server_loop(t_node *node)
{
	int	max_sd;
	int	activity;

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
	char	buf[BUFFER_SIZE];
	size_t	rsize;

	if (node->type == SERVER)
		server_loop(node);
	else
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
		init_client(&node, "127.0.0.1");
	loop(&node);
}
