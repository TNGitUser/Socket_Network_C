
#include "socket.h"

void	receive_string(t_node *node)
{
	char	buffer[1025];
	char	*output;
	char	*tmp;
	size_t	recv;
	size_t	ssize[2];

	read(node->socket_fd, &recv, sizeof(recv));
	recv = ntohl(recv);
	buffer[1024] = '\0';
	output = NULL;
	ssize[0] = 0;
	if (recv >= 1024)
		while ((ssize[1] = read(node->socket_fd, buffer, 1024)) > 0)
		{
			buffer[ssize[1]] = '\0';
			tmp = strjoin(output, buffer);
			if (output)
				free(output);
			output = tmp;
			ssize[0] += ssize[1];
		}
	else
	{
		buffer[read(node->socket_fd, buffer, 1024)] = '\0';
		output = strjoin("", buffer);
		ssize[0] = strlen(output);
	}
	printf("Received string : %s\n", output);
	printf("Validity : %3li%%\n", ssize[0] / recv * 100);
}
