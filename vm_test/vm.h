/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 15:03:43 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/28 19:51:11 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libdodo.h"
# include "op.h"
# include <fcntl.h>

t_vm	*init_vm(void);
void	parse_params(t_vm *vm, unsigned char *str, int *to_read,
														unsigned int *final);
void	print_memory(const void *addr, size_t size);
int		op_live(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_ld(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_st(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_add(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_sub(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_and(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_or(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_xor(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_zjmp(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_ldi(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_sti(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_fork(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_lld(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_lldi(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_lfork(t_vm *vm, t_process *process, unsigned int *params, int len);
int		op_aff(t_vm *vm, t_process *process, unsigned int *params, int len);

#endif
