
#include "socket.h"
#include "unistd.h"

static void	set_name_base(t_node *node, char *text)
{
	size_t	name_count;
	size_t	id;
	char	*name;

	name_count = strocc(text, '\n');
	if (name_count == 0)
		return ;
	if (!(node->namebase.names = malloc(sizeof(char *) * (name_count + 3))))
		error("Failed to malloc name base");
	id = 0;
	node->namebase.count = name_count + 2;
	node->namebase.names[name_count + 1] = NULL;
	node->namebase.names[name_count + 2] = NULL;
	while (*text)
	{
		name = strdelim(&text, '\n');
		node->namebase.names[id++] = name;
		if (!(*text))
			break ;
		if (*text == '\n')
			++text;
	}
}

void	get_name_file(t_node *node)
{
	char	*text;

	if (access(NAME_BASE, F_OK))
		return ;
	text = get_data_filename(NAME_BASE);
	set_name_base(node, text);
	if (text)
		free(text);
}

void		get_client_name(t_node *node, int id)
{
	int	name_id;

	name_id = rand() % (node->namebase.count);
	node->clients[id].name = node->namebase.names[name_id];
	node->clients[id].name_id = name_id;
	node->clients[id].color[0] = rand() % 256;
	node->clients[id].color[0] = rand() % 256;
	node->clients[id].color[0] = rand() % 256;
	printf("Client name : [%s]\n", node->clients[id].name);
}
