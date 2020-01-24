
#include "socket.h"

int		server_send_command(t_node *node, int client_fd, char *cmd, int prot)
{
	(void)node;
	(void)client_fd;
	(void)cmd;
	// Send command
	// Wait for confirmation
	return (0);
}

void	server_to_client(t_node *node, int client_id, char *cmd, int prot)
{
	(void)node;
	(void)client_id;
	(void)cmd;
	if (prot == GREET_CLIENT)
	{
	}
	else if (prot == SEND_FILE)
	{
	}
	else if (prot == CLOSE_CLIENT)
	{
	}
	else
		printf("\033[32mUnknown command\033[0m\n");
}
