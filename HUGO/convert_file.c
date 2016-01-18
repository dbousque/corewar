/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 15:59:39 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/18 16:07:43 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int				error_while_reading(char *filename)
{
	ft_putstr_fd("Error while reading file ", 2);
	ft_putendl_fd(filename, 2);
	return (0);
}

int				convert_file(char *filename)
{
	t_function *file;
	char		*line;
	int			ret;
	int			fd;
	int			test;

	file = NULL;
	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		return (cant_read_file(filename));
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		test = check_line(line);
		add_command(test, &file, line);
	}
	if (ret == -1)
		return (error_while_reading(filename));
	return (0);
}
