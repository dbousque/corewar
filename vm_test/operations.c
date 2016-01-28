/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 18:03:28 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/28 19:20:59 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char	valid_player(t_vm *vm, int dir_val)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (dir_val == vm->players[i]->number)
			return (1);
		i++;
	}
	return (0);
}

int		op_live(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	int		dir_val;

	dir_val = (int)params[0];
	//ft_printf("P    %d | live %d\n", process->number, dir_val);
	process->last_live = vm->current_cycle;
	process->nb_live++;
	if (valid_player(vm, dir_val))
		ft_putendl("LIVE !");
	return (len);
}

int		op_ld(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_st(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_add(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_sub(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_and(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_or(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_xor(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_zjmp(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_ldi(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_sti(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_fork(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_lld(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_lldi(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_lfork(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_aff(t_vm *vm, t_process *process, unsigned int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}
