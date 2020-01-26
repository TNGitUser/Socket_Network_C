
#include "socket.h"

int		server_get_active(t_node *node)
{
	int	act;
	int	i;

	i = 0;
	act = 0;
	while (i < MAXCON)
		if (node->clients[i++].active)
			++act;
	return (act);
}

void	server_get_workload(t_node *node, int act, int wl[2], int mod[2])
{
	(void)node;
	mod[0] = EX_WIDTH % (act + 1);
	mod[1] = EX_HEIGHT % (act + 1);
	wl[0] = EX_WIDTH / (act + 1);
	wl[1] = EX_HEIGHT / (act + 1);
}
