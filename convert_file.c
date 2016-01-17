

#include "corewar.h"

int				error_while_reading(char *filename)
{
	ft_putstr_fd("Error while reading file ", 2);
	ft_putendl_fd(filename, 2);
	return (0);
}

int				convert_file(char *filename)
{
	char	*line;
	int		ret;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		return (cant_read_file(filename));
	while ((ret = get_next_line(fd, &line)) == 1)
	{
	}
	if (ret == -1)
		return (error_while_reading(filename));
	return (0);
}
