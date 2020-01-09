
#include "socket.h"

static void	client_connect(int socket_fd, struct sockaddr *serv_addr
		, size_t addr_len)
{
	if (connect(socket_fd, serv_addr, addr_len) > 0)
		error("Connection failed");
}

void	init_client(t_node *node, char *server_address)
{
	int					socket_fd;
	struct sockaddr_in	serv_addr;

	socket_fd = -1;
	socket_fd = socket_init();
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, server_address, &serv_addr.sin_addr) <= 0)
		error("Invalid address / Error while converting address to binary");
	client_connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	node->addr = serv_addr;
	node->socket_fd = socket_fd;
	node->type = CLIENT;
}
