
#include "socket.h"

int		nerror(char *msg)
{
	printf("%s\n", msg);
	return (0);
}

void	error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
