#ifndef SOCKET_H
# define SOCKET_H

# include <unistd.h> 
# include <stdio.h> 
# include <sys/socket.h> 
# include <stdlib.h>
# include <arpa/inet.h>
# include <netinet/in.h> 
# include <string.h>
# include <time.h>

# define PORT			7654
# define MAXCON			10
# define BUFFER_SIZE	1024

# define CLIENT 2
# define SERVER 1

typedef	struct	s_node
{
	int					type;
	struct sockaddr_in	addr;
	struct sockaddr_in	serv_addr;
	int					socket_fd;
	fd_set				con_set;
	int					con_socket[MAXCON];

}				t_node;

int		socket_init();

void	init_server(t_node *node);
void	init_client(t_node *node, char *server_address);

void	set_add_child(t_node *node, int *max_fd);
void	manage_con_new(t_node *node);
void	manage_con_event(t_node *node);

void	error(char *msg);

#endif
