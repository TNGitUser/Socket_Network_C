
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

static void	send_string(int client_fd, t_node *node, char *string)
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

void	send_dummy(int client_fd, t_node *node)
{
	t_dummy dummy;

	dummy.status = client_fd - 3;
	dummy.msg = strdup("Bonjour ! je suis \033[0:34mCluster\033[0m ! Un assistant créé dans \
le but de permettre l'utilisation de plusieurs machines pour générer\
un rendu avec RT plus rapidement.");
	dummy.param = NULL;
	if (send(client_fd, &dummy, sizeof(dummy), 0) != sizeof(dummy))
		printf("Global dummy struct sending failed");
	send_string(client_fd, node, dummy.msg);
}
