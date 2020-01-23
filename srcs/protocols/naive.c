
#include "socket.h"

void	send_file(char *text, t_node *node, int client_fd)
{
	size_t	datalen;
	size_t	to_send;
	char	buffer[129];
	int		i;

	datalen = strlen(text);
	to_send = htonl(datalen);
	send(client_fd, &to_send, sizeof(to_send), 0);
	if (datalen > 128)
	{
		i = 0;
		while (i < datalen)
		{
			strncpy(buffer, text + i, 128);
			send(client_fd, &buffer, strlen(buffer), 0);
			i += 128;
		}
	}
	else
		send(client_fd, &text, datalen, 0);
}

void	receive_file(t_node *node)
{
	size_t	recv;
	size_t	rsize;
	char	*data;
	char	buffer[128 + 1];

	read(node->socket_fd, &recv, sizeof(recv), 0);
	recv = ntohl(recv);
	rsize = 0;
	data = strdup("");
	while (read(node->socket_fd, buffer, 128, 0) > 0)
	{
		strjoin();
	}
}
