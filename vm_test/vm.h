/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 15:03:43 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/31 12:48:32 by skirkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libdodo.h"
# include "op.h"
# include <fcntl.h>

# define PRINT_INSTR 1

extern int		g_error;

typedef struct	s_magic
{
	int			i;
	int			j;
	int			k;
	int			m;
	int			total;
	size_t		res;
}				t_magic;

t_vm			*init_vm(void);
void			go_to_next_byte(t_vm *vm, t_process *process);
unsigned char	*next_byte_nb(t_vm *vm, unsigned char *byte, int nb);
int				ft_pow(int nb, int pui);
void			dumpmemory(unsigned char *memory);
int				get_cycles_for_opcode(int opcode);
unsigned char	*next_instr(t_vm *vm, unsigned char *current_instr);
t_process		*new_process(unsigned char *start, int creation_cycle);
void			parse_params(t_vm *vm, unsigned char *str, int *to_read, int *final, int nb);
void			print_memory(const void *addr, size_t size);
int				op_live(t_vm *vm, t_process *process, int *params, int len);
int				op_ld(t_vm *vm, t_process *process, int *params, int len);
int				op_st(t_vm *vm, t_process *process, int *params, int len);
int				op_add(t_vm *vm, t_process *process, int *params, int len);
int				op_sub(t_vm *vm, t_process *process, int *params, int len);
int				op_and(t_vm *vm, t_process *process, int *params, int len);
int				op_or(t_vm *vm, t_process *process, int *params, int len);
int				op_xor(t_vm *vm, t_process *process, int *params, int len);
int				op_zjmp(t_vm *vm, t_process *process, int *params, int len);
int				op_ldi(t_vm *vm, t_process *process, int *params, int len);
int				op_sti(t_vm *vm, t_process *process, int *params, int len);
int				op_fork(t_vm *vm, t_process *process, int *params, int len);
int				op_lld(t_vm *vm, t_process *process, int *params, int len);
int				op_lldi(t_vm *vm, t_process *process, int *params, int len);
int				op_lfork(t_vm *vm, t_process *process, int *params, int len);
int				op_aff(t_vm *vm, t_process *process, int *params, int len);

#endif
