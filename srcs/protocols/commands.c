
#include "socket.h"

void	server_to_client(t_node *node, client_id, int cmd)
{
	if (cmd == GREET_CLIENT)
	{
	}
	else if (cmd == SEND_FILE)
	{
	}
	else if (cmd == CLOSE_CLIENT)
	{
	}
	else
		printf("\033[32mUnknown command\033[0m\n");
}
