
#include "socket.h"

int	cmd_run(t_node *node, char *cmd)
{
	(void)node;
	(void)cmd;
	// Do the supposed work 
	// For RT launch computation of the allocated area
	receive_file(node);
	return (0);
}
