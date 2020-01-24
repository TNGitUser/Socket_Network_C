
#include "socket.h"

void	send_time(t_node *node)
{
	time_t		current_time;
	struct tm	*time_info;
	char		time_string[10];

	time(&current_time);
	time_info = localtime(&current_time);
	strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);
	time_string[9] = '\0';
	printf("Client : %s\n", time_string);
	send(node->socket_fd, time_string, strlen(time_string), 0);
	sleep(5);
}

void	send_string(int client_fd, t_node *node, char *string)
{
	char	buffer[BUFFER_SIZE];
	size_t			len;
	size_t			var;

	(void)node;
	printf("%s\n", string);
	len = strlen(string);
	var = htonl(len);
	printf("Sent : %li\n", send(client_fd, &var, sizeof(var), 0));
	strcpy(buffer, string);
	buffer[len] = '\0';
	printf("Sent : %li\n", send(client_fd, &buffer, len, 0));
}

/*
**	CMD Example :	"SET		BOUNDS	0		0		250		250"
**					 COMMAND	VAR		startX	startY	endX	endY
*/

void	send_command(t_node *node, char *cmd, int client_id)
{
	send_string(node->clients[client_id].socket, node, cmd);
}
