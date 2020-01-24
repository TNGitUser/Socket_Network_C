
#include "socket.h"

static char	*get_cmd_bounds(int bounds[4])
{
	char	*tmp;
	char	*output;
	char	*bounds_c[4];

	bounds_c[0] = ft_itoa(bounds[0]);
	bounds_c[1] = ft_itoa(bounds[1]);
	bounds_c[2] = ft_itoa(bounds[2]);
	bounds_c[3] = ft_itoa(bounds[3]);
	tmp = ft_strnjoin(bounds_c[0], " ", bounds_c[1]);
	ft_memdel((void **)&bounds_c[0]);
	ft_memdel((void **)&bounds_c[1]);
	output = ft_strnjoin(tmp, " ", bounds_c[2]);
	ft_memdel((void **)&bounds_c[2]);
	ft_memdel((void **)&tmp);
	tmp = ft_strnjoin(output, " ", bounds_c[3]);
	ft_memdel((void **)&output);
	ft_memdel((void **)&bounds_c[3]);
	if (!tmp)
		error("Failed to convert bounds to string");
	return (tmp);
}

char		*get_set_cmd(int cmd_t, t_client client, int bounds[4])
{
	char	*tmp;
	char	*output;

	if (cmd_t == 0)
	{
		tmp = strnjoin("SET CLIENT '", client.name, "'");
		output = strnjoin(tmp, " ", color_to_string(client.color));
		ft_memdel((void **)&tmp);
	}
	else if (cmd_t == 1 && bounds)
	{
		tmp = get_cmd_bounds(bounds);
		output = strjoin("SET BOUNDS ", tmp);
		ft_memdel((void **)&tmp);
	}
	else
		error("Unknown protocol for get_set_cmd");
	return (output);
}
