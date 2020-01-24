
#include "socket.h"

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

char		*get_data_filename(char *file)
{
	char	*data;
	char	*str;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 3)
		error("Get_data_filename failed open");
	if (!(str = malloc(sizeof(char) * (128 + 1))))
		error("Get_data_filename malloc failed");
	data = read_file(fd, str);
	if (close(fd))
		error("Get_data_filename close failed");
	return (data);
}

char		*get_data()
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
	if (close(fd))
		error("Get_data close failed");
	return (data);
}
