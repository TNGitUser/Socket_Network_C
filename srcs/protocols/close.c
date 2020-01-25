
#include "socket.h"

int	cmd_close(t_node *node, char *cmd)
{
	(void)node;
	(void)cmd;
	printf("You were asked to be close\n");
	close(node->socket_fd);
	node->info.active = 0;
	ft_memdel((void **)&node->info.name);
	ft_memdel((void **)&node->param);
	return (0);
}
