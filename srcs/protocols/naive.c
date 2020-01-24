
#include "socket.h"

void	send_file(char *text, t_node *node, int client_fd)
{
	size_t	datalen;
	size_t	to_send;
	char	buffer[129];
	size_t	i;

	(void)node;
	datalen = strlen(text);
	to_send = htonl(datalen);
	send(client_fd, &to_send, sizeof(to_send), 0);
	if (datalen > 128)
	{
		i = 0;
		while (i < datalen)
		{
			strncpy(buffer, text + i, 128);
			printf("Sending : \n%s\n", buffer);
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
	size_t	rsize[2];
	char	*data;
	char	buffer[128 + 1];
	char	*output;

	read(node->socket_fd, &recv, sizeof(recv));
	recv = ntohl(recv);
	printf("Expected size : %li\n", recv);
	rsize[0] = 0;
	data = strdup("");
	while ((rsize[1] = read(node->socket_fd, buffer, 128)) > 0)
	{
		rsize[0] += rsize[1];
		buffer[rsize[1]] = '\0';
		output = strjoin(data, buffer);
		free(data);
		data = output;
		printf("Current : %li\n", rsize[0]);
		printf("Received : \n\n%s\n\n", buffer);
		if (rsize[0] >= recv)
			break ;
	}
	printf("Received : \n\n%s\n\n", output);
}
