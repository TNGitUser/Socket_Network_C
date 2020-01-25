
#include "socket.h"

int		server_send_init(t_node *node, int client_fd, char *cmd)
{
	send_string(client_fd, node, cmd);
	// Send command
	// Wait for confirmation | WARNING : Not implemented yet
	return (0);
}

void	server_to_client(t_node *node, int client_id, char *cmd, int prot)
{
	if (prot == GREET_CLIENT)
		server_send_init(node, node->clients[client_id].socket, cmd);
	else if (prot == SET_BOUNDS)
		server_send_init(node, node->clients[client_id].socket, cmd);
	else if (prot == SEND_FILE)
	{
		// Need to send command string for send file (client must be ready to
		// get file (which in RT case is the scene)
	}
	else if (prot == CLOSE_CLIENT)
	{
	}
	else
		printf("\033[32mUnknown command\033[0m\n");
}

void	await_command(t_node *node)
{
	int		status;
	char	*cmd;

	cmd = receive_string(node, &status);
	if (!status)
	{
		printf("Error : received failed");
		return ;
	}
	if (!is_command(cmd, &status))
	{
		printf("Error : unkown command\n[%s]\n", cmd);
		return ;
	}
	cmd_dispatch(node, cmd, &status);
	ft_memdel((void **)&cmd);
}
