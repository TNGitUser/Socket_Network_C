
#include "socket.h"

static void set_close_child(t_node *node, int client_id)
{
	int	client_fd;
	size_t	addr_len;

	addr_len = sizeof(node->addr);
	client_fd = node->con_socket[client_id];
	getpeername(client_fd, (struct sockaddr *)&node->addr
			, (socklen_t *)&addr_len);
	printf("\033[33mClient %i disconnected\033[0m : %s:%d\n", client_id
			, inet_ntoa(node->addr.sin_addr), ntohs(node->addr.sin_port));
	close(client_fd);
	node->clients[client_id].active = 0;
	node->con_socket[client_id] = 0;
}

static void	set_new_child(t_node *node, int client_fd, int *id)
{
	int	i;

	i = -1;
	while (++i < MAXCON)
	{
		if (node->con_socket[i] == 0)
		{
			node->con_socket[i] = client_fd;
			*id = i;
			break ;
		}
	}
}

void	set_add_child(t_node *node, int *max_fd)
{
	int	client;
	int	client_fd;

	client = -1;
	while (++client < MAXCON)
	{
		client_fd = node->con_socket[client];
		if (client_fd > 0)
			FD_SET(client_fd, &node->con_set);
		if (client_fd > *max_fd)
			*max_fd = client_fd;
	}
}

void	manage_con_new(t_node *node)
{
	int		client_fd;
	size_t	addr_len;
	int		id;
	char	*cmd;

	addr_len = sizeof(node->addr);

	if ((client_fd = accept(node->socket_fd, (struct sockaddr *)&node->addr,
					(socklen_t *)&addr_len)) < 0)
		error("Connection from client failed.");
	if (node->lock)
	{
		printf("Server locked. New connection denied\n");
		cmd = get_other_cmd(CLOSE_CLIENT, node);
		server_send(node, client_fd, cmd);
		ft_memdel((void **)&cmd);
		return ;
	}
	//printf("\nNew connection from %s:%d\n", inet_ntoa(node->addr.sin_addr)
	//		, ntohs(node->addr.sin_port));
	//printf("Client fd : %i\n", client_fd);

	set_new_child(node, client_fd, &id);
	get_client_name(node, id);
	node->clients[id].socket = client_fd;
	node->clients[id].active = 1;
	node->clients[id].set = 0;
	node->clients[id].ready = 0;
	cmd = get_set_cmd(0, node->clients[id], NULL);
	server_to_client(node, id, cmd, SET_CLIENT);
	ft_memdel((void **)&cmd);
}

void	manage_con_event(t_node *node)
{
	int		client_id;
	int		sd;
	size_t	rbyte;
	char	buffer[BUFFER_SIZE + 1];

	client_id = -1;
	while (++client_id < MAXCON)
	{
		bzero(buffer, BUFFER_SIZE);
		sd = node->con_socket[client_id];
		if (FD_ISSET(sd, &node->con_set))
		{
			if ((rbyte = read(sd, buffer, BUFFER_SIZE)) == 0
					|| buffer[0] == '\0')
				set_close_child(node, client_id);
			else
			{
				buffer[rbyte] = '\0';
				printf("Client %i sent : %s\n", client_id, buffer);
			}
		}
	}
}
