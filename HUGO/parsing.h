/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 16:00:06 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/17 16:29:20 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libdodo.h"
# include "op.h"
# include <fcntl.h>

# define OPCODE 1
# define INDIR 2
# define DIRE 3

typedef struct s_function	t_function;
typedef struct s_line		t_line;
typedef struct s_instruct	t_instruct;

struct			s_function
{
	char		*label;
	t_line		*lines;
};

struct			s_line
{
	int			numero;
	t_instruct	content;
	t_line		next;
};

struct			s_instruct
{
	char		*name;
	int			type;
	int			opcode;
	t_instrcut	next;
};

extern t_op		op_tab[17];

int				convert_file(char *filename);
int				cant_read_file(char *filename);
int				cant_create_file(char *filename);
int				create_res_file(char *filename, char **filename_res);
