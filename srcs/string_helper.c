
#include "socket.h"

char	*strdelim(char **src, char c)
{
	char	*output;
	size_t	l;

	l = 0;
	while ((*src)[l] && (*src)[l] != c)
		++l;
	if (!(output = malloc(sizeof(char) * (l + 1))))
		error("strdelim malloc error");
	output[l] = '\0';
	strncpy(output, *src, l);
	*src += l;
	return (output);
}

size_t	strocc(char *src, char c)
{
	size_t count;

	if (!src || c == '\0')
		return (0);
	count = 0;
	while (*src)
	{
		if (*src == c)
			++count;
		++src;
	}
	return (count);
}

char	*strnjoin(char *src, char *add, char *end)
{
	char	*output;
	int		i;

	if (!src || !add || !end || !(output = malloc(sizeof(char)
					* (strlen(src) + strlen(add) + strlen(end) + 1))))
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
	while (*end)
	{
		output[i++] = *end;
		++end;
	}
	output[i] = '\0';
	return (output);
}

char	*strjoin(char *src, char *add)
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
