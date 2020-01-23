
#include "socket.h"

static char	*strjoin(char *src, char *add)
{
	char	*output;
	int		i;

	if (!src || !add)
		return (NULL);
	if (!(output = malloc(sizeof(char) * (strlen(src) + strlen(add) + 1))))
		return (NULL);
	i = 0;
	while (*src)
	{
		output[i++] = *src;
		++src;
	}
	while (*add)
	{
		output[i++] = *add;
		++add;
	}
	output[i] = '\0';
	return (output);
}

static char	*read_file(int fd, char *str)
{
	char	*tmp;
	char	*input;
	int		rb;

	if (!(input = malloc(sizeof(char) * 2)))
		error("Read_file malloc failed");
	input[0] = '\0';
	rb = 128;
	while (rb == 128)
	{
		if ((rb = read(fd, str, 128)) == -1)
			error("Read_file read error");
		str[rb] = '\0';
		tmp = input;
		input = strjoin(input, str);
		free(tmp);
	}
	free(str);
	return (input);
}

void		get_data()
{
	char	target[1024];
	char	*data;
	char	*str;
	int		fd;

	printf("Please input target file : ");
	scanf("%s", target);
	if ((fd = open(target, O_RDONLY)) < 3)
		error("Get_data failed open");
	if (!(str = malloc(sizeof(char) * (128 + 1))))
		error("Get_data malloc failed");
	data = read_file(fd, str);
}
