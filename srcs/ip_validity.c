
#include "socket.h"

int	is_ip_valid(char *ip)
{
	struct sockaddr_in	addr;
	int					res;

	res = inet_pton(AF_INET, ip, &(addr.sin_addr));
	return (res != 0);
}
