/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirkovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 12:23:37 by skirkovs          #+#    #+#             */
/*   Updated: 2016/01/31 12:23:38 by skirkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		op_ld(t_vm *vm, t_process *process, int *params, int len)
{
	int				val;
	unsigned char	*addr;

	if (valid_reg(params[1]))
	{
		if (type_of_n_param(vm, process, 0) == DIR_CODE)
			val = params[0];
		else
		{
			addr = vm->memory + ((((short)params[0]) % IDX_MOD) +
					(process->next_instr - vm->memory)) % MEM_SIZE;
			val = get_val_at(vm, addr, 4);
		}
		if (PRINT_INSTR)
			ft_printf("P%5d | ld %d r%d\n", process->number, val, params[1]);
		process->registres[params[1] - 1] = val;
		if (val == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	return (len);
}

int		op_ldi(t_vm *vm, t_process *process, int *params, int len)
{
	int				val1;
	int				val2;
	int				res;
	unsigned char	*addr;

	if (valid_reg(params[2]))
	{
		g_error = 0;
		val1 = get_val_of_n_param(vm, process, params, 0);
		if (g_error)
			return (len);
		val2 = get_val_of_n_param(vm, process, params, 1);
		if (g_error)
			return (len);
		addr = vm->memory + (((val1 + val2) % IDX_MOD) +
								(process->next_instr - vm->memory)) % MEM_SIZE;
		res = get_val_at(vm, addr, sizeof(int));
		process->registres[params[2] - 1] = res;
		if (PRINT_INSTR)
		{
			ft_printf("P%5d | ldi %s %s %s\n", process->number,
			print_val(val1, 0), print_val(val2, 0), print_val(params[2], 1));
		}
	}
	return (len);
}

int		op_lld(t_vm *vm, t_process *process, int *params, int len)
{
	int				val;
	unsigned char	*addr;

	if (valid_reg(params[1]))
	{
		if (type_of_n_param(vm, process, 0) == DIR_CODE)
			val = params[0];
		else
		{
			addr = get_real_addr_of_ind(vm, process->next_instr,
														(short)params[0], 0);
			val = get_val_at(vm, addr, 4);
		}
		if (PRINT_INSTR)
			ft_printf("P%5d | lld %d r%d\n", process->number, val, params[1]);
		process->registres[params[1] - 1] = val;
		if (val == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	return (len);
}

int		op_lldi(t_vm *vm, t_process *process, int *params, int len)
{
	int		val1;
	int		val2;
	int		res;

	if (valid_reg(params[2]))
	{
		g_error = 0;
		val1 = get_val_of_n_param(vm, process, params, 0);
		if (g_error)
			return (len);
		val2 = get_val_of_n_param(vm, process, params, 1);
		if (g_error)
			return (len);
		res = get_val_at(vm, get_real_addr_of_ind(vm, process->next_instr,
													val1 + val2, 1), REG_SIZE);
		process->registres[params[2] - 1] = res;
		process->carry = ((val1 + val2) == 0);
		if (PRINT_INSTR)
		{
			ft_printf("P%5d | lldi %s %s %s\n", process->number,
			print_val(val1, 0), print_val(val2, 0), print_val(params[2], 1));
		}
	}
	return (len);
}
