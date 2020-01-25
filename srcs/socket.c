
#include "socket.h"

int			socket_init()
{
	int socket_fd;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == 0)
		error("Socket creation failed");
	return (socket_fd);
}

static void	socket_setopt(int socket_fd, struct sockaddr_in *address)
{
	int	opt;

	opt = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt
				, sizeof(opt)))
		error("Socket option binding failed");
	address->sin_family = AF_INET;
	address->sin_addr.s_addr = INADDR_ANY;
	address->sin_port = htons(PORT);
}

static void	socket_bind(int socket_fd, struct sockaddr_in *address)
{
	if (bind(socket_fd, (struct sockaddr *)address, sizeof(*address)) < 0)
		error("Socket bind failed");
	if (listen(socket_fd, MAXCON) < 0)
		error("Socket listening failed");
}

static void	socket_client_init(t_node *node)
{
	int	client;

	client = -1;
	while (++client < MAXCON)
		node->con_socket[client] = 0;
}

void		init_server(t_node *node)
{
	int					socket_fd;
	struct sockaddr_in	address;

	srand(time(NULL));
	socket_fd = -1;
	socket_fd = socket_init();
	socket_setopt(socket_fd, &address);
	socket_bind(socket_fd, &address);
	socket_client_init(node);
	node->addr = address;
	node->serv_addr = address;
	node->socket_fd = socket_fd;
	node->type = SERVER;
	node->err = 0;
	get_name_file(node);
}
