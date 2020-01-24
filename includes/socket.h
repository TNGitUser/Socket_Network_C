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
# include <fcntl.h>

# include "libft.h"

# define PORT			7654
# define MAXCON			10
# define BUFFER_SIZE	1024

# define CLIENT 2
# define SERVER 1

# define NAME_BASE	"data/names.dat"

# define GREET_CLIENT 0
# define SEND_FILE 1
# define CLOSE_CLIENT 9

typedef struct	s_name_base
{
	char		**names;
	size_t		count;
}				t_name_base;

typedef struct	s_client
{
	int			active;
	int			socket;
	char		*name;
	int			name_id;
	int			color[3];
}				t_client;

typedef	struct	s_node
{
	size_t				id;
	int					type;
	struct sockaddr_in	addr;
	struct sockaddr_in	serv_addr;
	int					socket_fd;
	fd_set				con_set;
	int					con_socket[MAXCON];
	t_client			clients[MAXCON];
	t_client			info;
	t_name_base			namebase;

}				t_node;

int		socket_init();

void	init_server(t_node *node);
void	init_client(t_node *node, char *server_address);

void	set_add_child(t_node *node, int *max_fd);
void	manage_con_new(t_node *node);
void	manage_con_event(t_node *node);

int		is_ip_valid(char *addr);

void	send_time(t_node *node);	

char	*get_data_filename(char *file);
char	*get_data();

void	send_file(char *text, t_node *node, int client_fd);
void	receive_file(t_node *node);

void	get_name_file(t_node *node);
void	get_client_name(t_node *node, int id);

char	*get_set_cmd(int cmd_t, t_client client, int bounds[4]);
void	server_to_client(t_node *node, int client_id, char *cmd, int prot);

void	string_to_color(char *str, t_node *node);
char	*color_to_string(int colors[3]);

char	*strdelim(char **src, char c);
size_t	strocc(char *src, char c);
char	*strnjoin(char *src, char *add, char *end);
char	*strjoin(char *src, char *add);

void	error(char *msg);

#endif
