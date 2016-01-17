

#ifndef COREWAR_H
# define COREWAR_H

# include "libdodo.h"
# include "op.h"
# include <fcntl.h>

extern t_op op_tab[17];

int		convert_file(char *filename);
int		cant_read_file(char *filename);
int		cant_create_file(char *filename);
int		create_res_file(char *filename, char **filename_res);

#endif
