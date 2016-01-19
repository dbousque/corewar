/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_bytecode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:24:25 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/19 17:54:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	functions->header = 1;
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
	functions->next->next->lines->next->next = (t_line*)malloc(sizeof(t_line));
	functions->next->next->lines->next->next->next = NULL;

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

	functions->next->next->lines->next->next->numero = 2;
	functions->next->next->lines->next->next->content = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->next->lines->next->next->content->name = "zjmp";
	functions->next->next->lines->next->next->content->type = OPCODE;
	functions->next->next->lines->next->next->content->opcode = 9;
	functions->next->next->lines->next->next->content->next = (t_instruct*)malloc(sizeof(t_instruct));
	functions->next->next->lines->next->next->content->next->name = "%:live";
	functions->next->next->lines->next->next->content->next->type = DIRE;
	functions->next->next->lines->next->next->content->next->next = NULL;
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
	int		i;

	if (!(res_filename = (char**)malloc(sizeof(char*))))
		return (cant_create_file(NULL));
	*res_filename = NULL;
	if ((fd = create_res_file(filename, res_filename)) == -1)
		return (cant_create_file(*res_filename));
	ft_printf("Writing output program to %s\n", *res_filename);
	while (bytes)
	{
//		ft_putendl("BYTE!");
		//ft_printf("%d\n", *(unsigned char*)bytes->content);
		i = bytes->content_size - 1;
		while (i >= 0)
		{
			write(fd, bytes->content + i, 1);
			i--;
		}
		//write(fd, bytes->content, bytes->content_size);
		bytes = bytes->next;
	}
	return (0);
}

int			big_error(void)
{
	ft_putendl_fd("BIG ERROR", 2);
	return (0);
}

void		*big_error_null(void)
{
	ft_putendl_fd("BIG ERROR", 2);
	return (NULL);
}

int			write_opcode(unsigned char opcode, t_list **bytes_end)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(&opcode, sizeof(unsigned char))))
		return (0);
	ft_lstaddend(bytes_end, tmp);
	return (1);
}

t_op		*get_opcode_descr_with_opcode(int opcode)
{
	int		i;

	i = 0;
	while (op_tab[i].name)
	{
		if (op_tab[i].opcode == opcode)
			return (&(op_tab[i]));
		i++;
	}
	return (NULL);
}

unsigned char	set_two_bits_from(unsigned char byte, unsigned char bits, int from)
{
	from = 8 - from;
	byte = (byte | (bits<<(from - 2)));
	return (byte);
}

int			write_param_byte_if_nec(t_instruct *instruct, t_list **bytes_end,
														t_function *function)
{
	t_list			*tmp;
	t_op			*opcode;
	unsigned char	param_byte;
	int				decal;

	if (!(opcode = get_opcode_descr_with_opcode(instruct->opcode)))
		return (big_error());
	if (!opcode->has_param_byte)
		return (1);
	param_byte = 0;
	decal = 0;
	instruct = instruct->next;
	while (instruct)
	{
		if (instruct->type == REG)
			param_byte = set_two_bits_from(param_byte, REG_CODE, decal);
		else if (instruct->type == INDIR)
			param_byte = set_two_bits_from(param_byte, IND_CODE, decal);
		else if (instruct->type == DIRE)
			param_byte = set_two_bits_from(param_byte, DIR_CODE, decal);
		else
			return (big_error());
		decal += 2;
		instruct = instruct->next;
	}
	if (!(tmp = ft_lstnew(&param_byte, sizeof(unsigned char))))
		return (0);
	ft_lstaddend(bytes_end, tmp);
	function->bytes_written++;
	return (1);
}

unsigned long long	get_relative_addr_of_label(char *label, t_function *function,
														t_function *functions)
{
	unsigned long long	res;
	unsigned int		bytes_written;
	int					found;

	found = 0;
	res = 0;
	bytes_written = 0;
	ft_putendl(label);
	while (functions)
	{
		if (ft_strcmp(functions->label, label) == 0)
			found = 1;
		if (found)
			bytes_written += functions->bytes_written;
		if (functions == function)
			return (res - bytes_written + 1);
		functions = functions->next;
	}
	return (res);
}

int			label_not_found(char *label)
{
	ft_putstr_fd("LABEL NOT FOUND : ", 2);
	ft_putendl_fd(label, 2);
	return (0);
}

typedef struct	s_to_resolve
{
	char		*label_to_seek;
	t_function	*function_from;
	int			bytes_written_in_function_from;
	t_list		*byte_to_override;
	int			small_dir;
}				t_to_resolve;

t_to_resolve	*new_resolve(char *label, t_function *function_from,
							int bytes_written_from, t_list *byte_to_override)
{
	t_to_resolve	*res;
	if (!(res = (t_to_resolve*)malloc(sizeof(t_to_resolve))))
		return (NULL);
	res->label_to_seek = ft_strdup(label);
	res->function_from = function_from;
	res->bytes_written_in_function_from = bytes_written_from;
	res->byte_to_override = byte_to_override;
	return (res);
}

void		replace_bytes(t_list *bytes, void *val, size_t size)
{
	void	*res;

	res = malloc(size);
	ft_memcpy(res, val, size);
	bytes->content = res;
	bytes->content_size = size;
}

int			resolve_unresolved_labels(t_list *labels_to_resolve)
{
	t_function		*tmp_function;
	t_to_resolve	*to_res;
	unsigned int	bytes_inbetween;
	char			done;
	int				tour;

	while (labels_to_resolve)
	{
		done = 0;
		tour = 0;
		to_res = ((t_to_resolve*)labels_to_resolve->content);
		ft_printf("end : %d, tmp : %d\n", to_res->function_from->bytes_written, to_res->bytes_written_in_function_from);
		bytes_inbetween = to_res->function_from->bytes_written - to_res->bytes_written_in_function_from + 1;
		tmp_function = to_res->function_from->next;
		while (tmp_function && !done)
		{
			if (ft_strcmp(to_res->label_to_seek, tmp_function->label) == 0)
			{
				ft_printf("bytes inbetween : %d\n", bytes_inbetween);
				if (tour && !to_res->small_dir)
					bytes_inbetween += 2;
				replace_bytes(to_res->byte_to_override, &bytes_inbetween, to_res->small_dir ? DIR_SIZE / 2 : DIR_SIZE);
				done = 1;
			}
			tour = 1;
			ft_printf("function : %s, bytes_written : %d\n", tmp_function->label, tmp_function->bytes_written);
			bytes_inbetween += tmp_function->bytes_written;
			tmp_function = tmp_function->next;
		}
		labels_to_resolve = labels_to_resolve->next;
	}
	return (1);
}

int			write_params(t_instruct *instruct, t_list **bytes_end,
									t_function *function, t_function *functions, t_list **labels_to_resolve, t_list **labels_to_resolve_end)
{
	t_list			*tmp;
	unsigned int	val_val;
	unsigned char	*val;
	t_op			*opcode;

	if (!(opcode = get_opcode_descr_with_opcode(instruct->opcode)))
		return (big_error());
	val = NULL;
	instruct = instruct->next;
	while (instruct)
	{
		ft_putendl(instruct->name);
		if (instruct->type == INDIR)
		{
			val_val = ft_atoi(instruct->name);
			val = (unsigned char*)&val_val;
			tmp = ft_lstnew(val, IND_SIZE);
			ft_lstaddend(bytes_end, tmp);
			function->bytes_written += IND_SIZE;
		}
		else if (instruct->type == REG)
		{
			val_val = ft_atoi(instruct->name + 1);
			val = (unsigned char*)&val_val;
			tmp = ft_lstnew(val, REG_SIZE);
			ft_lstaddend(bytes_end, tmp);
			function->bytes_written += REG_SIZE;
		}
		else if (instruct->type == DIRE)
		{
			if (instruct->name[1] == LABEL_CHAR)
			{
				val_val = get_relative_addr_of_label(instruct->name + 2, function, functions);
				val = (unsigned char*)&val_val;
				tmp = ft_lstnew(val, opcode->small_dir ? DIR_SIZE / 2 : DIR_SIZE);
				ft_lstaddend(bytes_end, tmp);
				if (val_val == (unsigned int)1)
				{
					ft_lstaddend(labels_to_resolve_end, ft_lstnew(new_resolve(instruct->name + 2, function, function->bytes_written, *bytes_end), sizeof(t_to_resolve)));
					if (!*labels_to_resolve)
						*labels_to_resolve = *labels_to_resolve_end;
					((t_to_resolve*)(*labels_to_resolve_end)->content)->small_dir = opcode->small_dir;
				}
			}
			else
			{
				val_val = ft_atoi(instruct->name + 1);
				val = (unsigned char*)&val_val;
				tmp = ft_lstnew(val, opcode->small_dir ? DIR_SIZE / 2 : DIR_SIZE);
				ft_lstaddend(bytes_end, tmp);
			}
			function->bytes_written += opcode->small_dir ? DIR_SIZE / 2 : DIR_SIZE;
		}
		else
			return (0);
		instruct = instruct->next;
	}
	return (1);
}

int			write_void_byte(t_list **bytes_end)
{
	t_list			*tmp;
	unsigned char	zero;

	zero = 0;
	if (!(tmp = ft_lstnew(&zero, sizeof(unsigned char))))
		return (0);
	ft_lstaddend(bytes_end, tmp);
	return (1);
}

int			add_functions(t_function *functions, t_list **bytes_end)
{
	t_function	*tmp_function;
	t_line		*tmp_line;
	t_instruct	*tmp_instruct;
	t_list		*labels_to_resolve;
	t_list		*labels_to_resolve_end;

	labels_to_resolve = NULL;
	labels_to_resolve_end = NULL;
	tmp_function = functions;
	while (tmp_function)
	{
		tmp_function->bytes_written = 0;
		tmp_line = tmp_function->lines;
		while (tmp_line)
		{
			/*tmp_instruct = tmp_line->content;
			while (tmp_instruct)
			{
				ft_printf("name : %s, type : %d, opcode : %d\n", tmp_instruct->name, tmp_instruct->type, tmp_instruct->opcode);
				tmp_instruct = tmp_instruct->next;
			}*/
			tmp_instruct = tmp_line->content;
			if (!(write_opcode(tmp_instruct->opcode, bytes_end)))
				return (big_error());
			tmp_function->bytes_written += 1;
			if (!(write_param_byte_if_nec(tmp_instruct, bytes_end, tmp_function)))
				return (big_error());
			if (!(write_params(tmp_instruct, bytes_end, tmp_function,
								functions, &labels_to_resolve, &labels_to_resolve_end)))
				return (big_error());
			tmp_line = tmp_line->next;
		}
		//if (!(write_void_byte(bytes_end)))
		//	return (big_error());
		tmp_function = tmp_function->next;
	}
	return (resolve_unresolved_labels(labels_to_resolve));
}

t_list		*add_header_to_bytes2(t_instruct *name, t_instruct *comment, t_list **bytes_end)
{
	int				i;
	int				x;
	unsigned char	zero;
	t_list			*prog_size;

	zero = 0;
	if (ft_strlen(name->name) > PROG_NAME_LENGTH
		|| ft_strlen(comment->name) > COMMENT_LENGTH)
		return (big_error_null());
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
	if (!(prog_size = ft_lstnew(NULL, 0)))
		return (NULL);
	ft_lstaddend(bytes_end, prog_size);
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
	return (prog_size);
}

t_list		*add_header_to_bytes(t_function *functions, t_list **bytes_end)
{
	t_instruct	*name;
	t_instruct	*comment;

	if (functions->header != 1)
		return (big_error_null());
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
		return (big_error_null());
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

int			update_size_bytes(t_list *size_bytes, t_function *functions)
{
	unsigned long long	prog_len;
	unsigned int		*res;

	prog_len = 0;
	while (functions)
	{
		prog_len += functions->bytes_written;
		functions = functions->next;
	}
	if (!(res = (unsigned int*)malloc(sizeof(unsigned int))))
		return (big_error());
	*res = (unsigned int)prog_len;
	size_bytes->content = res;
	size_bytes->content_size = sizeof(unsigned int);
	return (1);
}

int			convert_to_binary(t_function *functions, char *filename)
{
	t_list		*bytes;
	t_list		*bytes_end;
	t_list		*size_bytes;

	bytes = NULL;
	bytes_end = NULL;
	if (!(add_exec_magic_to_bytes(&bytes, &bytes_end)))
		return (0);
	ft_putendl("THEEERE TOO");
	if (!(size_bytes = add_header_to_bytes(functions, &bytes_end)))
		return (0);
	if (!(add_functions(functions->next, &bytes_end)))
		return (0);
	if (!(update_size_bytes(size_bytes, functions->next)))
		return (0);
	return (write_bytes_to_file(filename, bytes));
}

int			merge_first_two_functions(t_function **functions)
{
	t_function	*new_func;

	if (!(new_func = (t_function*)malloc(sizeof(t_function))))
		return (big_error());
	new_func->label = NULL;
	new_func->header = 1;
	new_func->bytes_written = 0;
	new_func->next = (*functions)->next->next;
	if (!(new_func->lines = (t_line*)malloc(sizeof(t_line))))
		return (big_error());
	if (!(new_func->lines->next = (t_line*)malloc(sizeof(t_line))))
		return (big_error());
	if (!(new_func->lines->content = (t_instruct*)malloc(sizeof(t_instruct))))
		return (big_error());
	if (!(new_func->lines->next->content = (t_instruct*)malloc(sizeof(t_instruct))))
		return (big_error());
	if (!(new_func->lines->content->next = (t_instruct*)malloc(sizeof(t_instruct))))
		return (big_error());
	if (!(new_func->lines->next->content->next = (t_instruct*)malloc(sizeof(t_instruct))))
		return (big_error());
	new_func->lines->next->next = NULL;
	new_func->lines->content->next->next = NULL;
	new_func->lines->next->content->next->next = NULL;
	new_func->lines->content->name = ft_strdup(NAME_CMD_STRING);
	new_func->lines->next->content->name = ft_strdup(COMMENT_CMD_STRING);
	if ((*functions)->header == 1)
	{
		(*functions)->label[ft_strlen((*functions)->label) - 1] = '\0';
		new_func->lines->content->next->name = ft_strdup((*functions)->label + 1);
		(*functions)->next->label[ft_strlen((*functions)->next->label) - 1] = '\0';
		new_func->lines->next->content->next->name = ft_strdup((*functions)->next->label + 1);
	}
	else
	{
		(*functions)->label[ft_strlen((*functions)->label) - 1] = '\0';
		new_func->lines->next->content->next->name = ft_strdup((*functions)->label + 1);
		(*functions)->next->label[ft_strlen((*functions)->next->label) - 1] = '\0';
		new_func->lines->content->next->name = ft_strdup((*functions)->next->label + 1);
	}
	ft_printf("comment : %s, name : %s\n", new_func->lines->content->name, new_func->lines->next->content->name);
	*functions = new_func;
	return (1);
}

int			convert_to_bytecode(t_function *functions, char *filename)
{
	if (!(merge_first_two_functions(&functions)))
		return (0);
	ft_putendl("THERE");
	convert_to_binary(functions, filename);
	return (0);
}
