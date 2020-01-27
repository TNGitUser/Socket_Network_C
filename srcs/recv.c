
#include "socket.h"

char	*receive_string(t_node *node, int *status)
{
	char	buffer[1025];
	char	*output;
	char	*tmp;
	ssize_t	recv;
	ssize_t	ssize[2];

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
	else if (recv > 0)
	{
		buffer[read(node->socket_fd, buffer, 1024)] = '\0';
		output = strjoin("", buffer);
		ssize[0] = strlen(output);
	}
	printf("Received string : %s\n", output);
	if (recv > 0)
		printf("Validity : %3li%%\n", ssize[0] / recv * 100);
	*status = recv > 0 ? (ssize[0] / recv * 100) == 100 : 1;
	return (output);
}
