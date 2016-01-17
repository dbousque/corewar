

#include "convert_to_bytecode.h"

t_function	*get_functions(char *filename)
{
	t_function	*functions;

	(void)filename;
	functions = (t_function*)malloc(sizeof(t_function));
	functions->next = (t_function*)malloc(sizeof(t_function));
	functions->next->next = (t_function*)malloc(sizeof(t_function));
	functions->next->next->next = NULL;

	functions->label = "header";
	functions->lines = (t_line*)malloc(sizeof(t_line));
	functions->lines->next = (t_line*)malloc(sizeof(t_line));
	functions->lines->numero = 0;
	functions->lines->content = (t_instruct*)malloc(sizeof(t_instruct));
	functions->lines->content->name = ".name";
	functions->lines->content->type = HEADER;
	functions->lines->content->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->lines->content->next->name = "zork";
	functions->lines->content->next->type = HEADER;
	functions->lines->content->next->next = NULL;
	functions->lines->next->numero = 1;
	functions->lines->next->content = (t_instruct*)malloc(sizeof(t_instruct));
	functions->lines->next->content->name = ".comment";
	functions->lines->next->content->type = HEADER;
	functions->lines->next->content->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->lines->next->content->next->name = "LOL ALIVE";
	functions->lines->next->content->next->type = HEADER;
	functions->lines->next->content->next->next = NULL;
	functions->lines->next->next = NULL;


	functions->next->label = "l2";
	functions->next->lines = (t_line*)malloc(sizeof(t_line));
	functions->next->lines->next = (t_line*)malloc(sizeof(t_line));
	functions->next->lines->next->next = NULL;

	functions->next->lines->numero = 0;
	functions->next->lines->content = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->content->name = "sti";
	functions->next->lines->content->type = OPCODE;
	functions->next->lines->content->opcode = 11;
	functions->next->lines->content->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->content->next->name = "r1";
	functions->next->lines->content->next->type = REG;
	functions->next->lines->content->next->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->content->next->next->name = "%:live";
	functions->next->lines->content->next->next->type = DIRE;
	functions->next->lines->content->next->next->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->content->next->next->next->name = "%1";
	functions->next->lines->content->next->next->next->type = DIRE;
	functions->next->lines->content->next->next->next->next = NULL;

	functions->next->lines->next->numero = 1;
	functions->next->lines->next->content = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->next->content->name = "and";
	functions->next->lines->next->content->type = OPCODE;
	functions->next->lines->next->content->opcode = 6;
	functions->next->lines->next->content->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->next->content->next->name = "r1";
	functions->next->lines->next->content->next->type = REG;
	functions->next->lines->next->content->next->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->next->content->next->next->name = "%0";
	functions->next->lines->next->content->next->next->type = DIRE;
	functions->next->lines->next->content->next->next->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->lines->next->content->next->next->next->name = "r1";
	functions->next->lines->next->content->next->next->next->type = REG;
	functions->next->lines->next->content->next->next->next->next = NULL;

	functions->next->next->label = "live";
	functions->next->next->lines = (t_line*)malloc(sizeof(t_line));
	functions->next->next->lines->next = (t_line*)malloc(sizeof(t_line));
	functions->next->next->lines->next->next = NULL;

	functions->next->next->lines->numero = 0;
	functions->next->next->lines->content = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->next->lines->content->name = "live";
	functions->next->next->lines->content->type = OPCODE;
	functions->next->next->lines->content->opcode = 1;
	functions->next->next->lines->content->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->next->lines->content->next->name = "%1";
	functions->next->next->lines->content->next->type = DIRE;
	functions->next->next->lines->content->next->next = NULL;

	functions->next->next->lines->next->numero = 1;
	functions->next->next->lines->next->content = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->next->lines->next->content->name = "zjmp";
	functions->next->next->lines->next->content->type = OPCODE;
	functions->next->next->lines->next->content->opcode = 9;
	functions->next->next->lines->next->content->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->next->lines->next->content->next->name = "%:live";
	functions->next->next->lines->next->content->next->type = DIRE;
	functions->next->next->lines->next->content->next->next = NULL;
	return (functions);
}

int		cant_create_file(char *filename)
{
	ft_putstr_fd("Failed to create binary file ", 2);
	if (filename)
		ft_putendl_fd(filename, 2);
	return (0);
}

int		get_last_point_index(char *filename)
{
	int		i;
	int		ind;

	ind = -1;
	i = 0;
	while (filename[i])
	{
		if (filename[i] == '.')
			ind = i;
		i++;
	}
	if (ind == -1)
		return (i);
	return (ind);
}

int		create_res_file(char *filename, char **filename_res)
{
	int		last_point;

	last_point = get_last_point_index(filename);
	if (!(*filename_res = (char*)malloc(sizeof(char) * (last_point + 5))))
		return (-1);
	(*filename_res)[last_point + 4] = '\0';
	ft_memcpy(*filename_res, filename, last_point);
	(*filename_res)[last_point] = '.';
	(*filename_res)[last_point + 1] = 'c';
	(*filename_res)[last_point + 2] = 'o';
	(*filename_res)[last_point + 3] = 'r';
	return (open(*filename_res, O_CREAT | O_TRUNC | O_RDWR));
}

int			write_bytes_to_file(char *filename, t_list *bytes)
{
	int		fd;
	char	**res_filename;

	if (!(res_filename = (char**)malloc(sizeof(char*))))
		return (cant_create_file(NULL));
	*res_filename = NULL;
	if ((fd = create_res_file(filename, res_filename)) == -1)
		return (cant_create_file(*res_filename));
	ft_printf("Writing output program to %s\n", *res_filename);
	while (bytes)
	{
		//ft_printf("%d\n", *(unsigned char*)bytes->content);
		write(fd, (unsigned char*)bytes->content, 1);
		bytes = bytes->next;
	}
	return (0);
}

int			big_error(void)
{
	ft_putendl_fd("BIG ERROR", 2);
	return (0);
}

int			add_header_to_bytes2(t_instruct *name, t_instruct *comment, t_list **bytes_end)
{
	int				i;
	int				x;
	unsigned char	zero;

	zero = 0;
	if (ft_strlen(name->name) > PROG_NAME_LENGTH
		|| ft_strlen(comment->name) > COMMENT_LENGTH)
		return (big_error());
	x = 0;
	while (name->name[x])
	{
		ft_lstaddend(bytes_end, ft_lstnew(&name->name[x], sizeof(char)));
		x++;
	}
	i = x;
	while (i < PROG_NAME_LENGTH)
	{
		ft_lstaddend(bytes_end, ft_lstnew(&zero, sizeof(unsigned char)));
		i++;
	}
	x = 0;
	while (comment->name[x])
	{
		ft_lstaddend(bytes_end, ft_lstnew(&comment->name[x], sizeof(char)));
		x++;
	}
	i = x;
	while (i < COMMENT_LENGTH)
	{
		ft_lstaddend(bytes_end, ft_lstnew(&zero, sizeof(unsigned char)));
		i++;
	}
	return (1);
}

int			add_header_to_bytes(t_function *functions, t_list **bytes_end)
{
	t_instruct	*name;
	t_instruct	*comment;

	if (ft_strcmp(functions->label, "header") != 0)
		return (big_error());
	if (ft_strcmp(functions->lines->content->name, NAME_CMD_STRING) == 0
		&& ft_strcmp(functions->lines->next->content->name, COMMENT_CMD_STRING) == 0)
	{
		name = functions->lines->content->next;
		comment = functions->lines->next->content->next;
	}
	else if (ft_strcmp(functions->lines->next->content->name, NAME_CMD_STRING) == 0
		&& ft_strcmp(functions->lines->content->name, COMMENT_CMD_STRING) == 0)
	{
		name = functions->lines->next->content->next;
		comment = functions->lines->content->next;
	}
	else
		return (big_error());
	return (add_header_to_bytes2(name, comment, bytes_end));
}

int			add_exec_magic_to_bytes(t_list **bytes, t_list **bytes_end)
{
	unsigned int	tmp;
	unsigned char	tmp_char;
	t_list			*tmp_list;

	tmp = COREWAR_EXEC_MAGIC;
	tmp_char = tmp / (256 * 256 * 256);
	tmp -= (tmp_char * 256 * 256 * 256);
	if (!(tmp_list = ft_lstnew(&tmp_char, sizeof(unsigned char))))
		return (0);
	ft_lstaddend(bytes_end, tmp_list);
	*bytes = *bytes_end;
	tmp_char = tmp / (256 * 256);
	tmp -= (tmp_char * 256 * 256);
	if (!(tmp_list = ft_lstnew(&tmp_char, sizeof(unsigned char))))
		return (0);
	ft_lstaddend(bytes_end, tmp_list);
	tmp_char = tmp / 256;
	tmp -= (tmp_char * 256);
	if (!(tmp_list = ft_lstnew(&tmp_char, sizeof(unsigned char))))
		return (0);
	ft_lstaddend(bytes_end, tmp_list);
	tmp_char = tmp;
	if (!(tmp_list = ft_lstnew(&tmp_char, sizeof(unsigned char))))
		return (0);
	ft_lstaddend(bytes_end, tmp_list);
	return (1);
}

int			convert_to_binary(t_function *functions, char *filename)
{
	//t_line		*line;
//	t_instruct	*instruct;
	t_list		*bytes;
	t_list		*bytes_end;

	bytes = NULL;
	bytes_end = NULL;
	if (!(add_exec_magic_to_bytes(&bytes, &bytes_end)))
		return (0);
	if (!(add_header_to_bytes(functions, &bytes_end)))
		return (0);
	/*functions = functions->next;
	while (functions)
	{
		line = functions->lines;
		ft_printf("FUNCTION NAME : %s\n", functions->label);
		while (line)
		{
			instruct = line->content;
			while (instruct)
			{
				ft_putendl(instruct->name);
				instruct = instruct->next;
			}
			line = line->next;
		}
		functions = functions->next;
	}*/
	return (write_bytes_to_file(filename, bytes));
}

int			main(int argc, char **argv)
{
	t_function	*functions;

	if (argc < 2)
		return (0);
	functions = get_functions(argv[argc - 1]);
	convert_to_binary(functions, argv[argc - 1]);
	return (0);
}
