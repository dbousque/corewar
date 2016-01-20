/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_bytecode.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 16:01:31 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/20 15:46:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_TO_BYTECODE_H
# define CONVERT_TO_BYTECODE_H

# include "libdodo.h"
# include <fcntl.h>
# include "parsing.h"

typedef struct		s_to_resolve
{
	char			*label_to_seek;
	t_function		*function_from;
	int				bytes_written_in_function_from;
	t_list			*byte_to_override;
	int				small_dir;
	int				opcode;
	int				has_param_byte;
}					t_to_resolve;

int					write_bytes_to_file(char *filename, t_list *bytes);
int					big_error(void);
void				*big_error_null(void);
int					update_size_bytes(t_list *size_bytes,
														t_function *functions);
int					merge_first_two_functions(t_function **functions);
t_list				*add_header_to_bytes(t_function *functions, 
														t_list **bytes_end);
int					add_exec_magic_to_bytes(t_list **bytes, t_list **bytes_end);
int					write_params(t_instruct *instruct, t_list **bytes_end,
	t_function *function, t_function *functions, t_list **labels_to_resolve,
												t_list **labels_to_resolve_end);
int					write_opcode(unsigned char opcode, t_list **bytes_end);
t_op				*get_opcode_descr_with_opcode(int opcode);
int					write_param_byte_if_nec(t_instruct *instruct,
									t_list **bytes_end, t_function *function);
unsigned long long	get_relative_addr_of_label(char *label,
					t_function *function, t_function *functions, t_op *opcode);
t_to_resolve		*new_resolve(char *label, t_function *function_from,
							int bytes_written_from, t_list *byte_to_override);
int					resolve_unresolved_labels(t_list *labels_to_resolve);

#endif