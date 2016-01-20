/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_bytecode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:24:25 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/20 17:29:36 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert_to_bytecode.h"

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
		ft_putendl(tmp_function->label);
		ft_putendl("LA");
		tmp_function->bytes_written = 0;
		tmp_line = tmp_function->lines;
		while (tmp_line)
		{
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
		tmp_function = tmp_function->next;
	}
	return (resolve_unresolved_labels(labels_to_resolve));
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
	if (!(size_bytes = add_header_to_bytes(functions, &bytes_end)))
		return (0);
	if (!(add_functions(functions->next, &bytes_end)))
		return (0);
	if (!(update_size_bytes(size_bytes, functions->next)))
		return (0);
	return (write_bytes_to_file(filename, bytes));
}

int			convert_to_bytecode(t_function *functions, char *filename)
{
	if (!(merge_first_two_functions(&functions)))
		return (0);
	convert_to_binary(functions, filename);
	return (0);
}
