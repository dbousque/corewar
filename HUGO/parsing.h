/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 16:00:06 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/17 16:01:14 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libdodo.h"
# include "op.h"
# include <fcntl.h>

extern t_op op_tab[17];

int		convert_file(char *filename);
int		cant_read_file(char *filename);
int		cant_create_file(char *filename);
int		create_res_file(char *filename, char **filename_res);
