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

int		type_of_n_param(t_vm *vm, t_process *process, int n)
{
	unsigned char	type;

	type = (*next_instr(vm, process->next_instr) >> (6 - (n * 2))) % 4;
	return (type);
}

unsigned char	*get_real_addr_of_ind(t_vm *vm, unsigned char *ori_addr,
																	int to_add)
{
	unsigned char	*addr;

	addr = ori_addr + (to_add % IDX_MOD);
	if (addr >= vm->memory + MEM_SIZE)
		addr = vm->memory + (addr - (vm->memory + MEM_SIZE));
	else if (addr < vm->memory)
		addr = vm->memory + MEM_SIZE - (vm->memory - addr);
	return (addr);
}

unsigned int	get_val_at(t_vm *vm, unsigned char *addr, int nb)
{
	int				pow;
	int				i;
	unsigned int	res;

	i = 0;
	res = 0;
	pow = nb - 1;
	while (pow >= 0)
	{
		res += *(next_byte_nb(vm, addr, i)) * ft_pow(256, pow);
		i++;
		pow--;
	}
	return (res);
}

void	copy_val_at(t_vm *vm, unsigned char *addr, unsigned int val, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		*(get_real_addr_of_ind(vm, addr, i)) = val / ft_pow(256, nb - i - 1);
		val -= (val / ft_pow(256, nb - i - 1)) * ft_pow(256, nb - i - 1);
		i++;
	}
}

char	valid_reg(int param)
{
	if (param > 0 && param <= 16)
		return (1);
	return (0);
}

int		op_live(t_vm *vm, t_process *process, int *params, int len)
{
	int		dir_val;

	dir_val = params[0];
	if (valid_reg(dir_val))
	{
		if (PRINT_INSTR)
			ft_printf("P%5d | live %d\n", process->number, dir_val);
		process->last_live = vm->current_cycle;
		process->nb_live++;
		//if (valid_player(vm, dir_val))
		//	ft_putendl("LIVE !");
	}
	return (len);
}

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
			addr = get_real_addr_of_ind(vm, process->next_instr,
															(short)params[0]);
			val = get_val_at(vm, addr, 4);
		}
		if (PRINT_INSTR)
			ft_printf("P%5d | ld %d r%d\n", process->number, val, params[1]);
		process->registres[params[1] - 1] = val;
	}
	return (len);
}

int		op_st(t_vm *vm, t_process *process, int *params, int len)
{
	unsigned char	*addr;

	if (valid_reg(params[0]))
	{
		if (type_of_n_param(vm, process, 1) == REG_CODE)
		{
			if (valid_reg(params[1]))
				process->registres[params[1] - 1] = process->registres[params[0] - 1];
			if (PRINT_INSTR)
				ft_printf("P%5d | st r%d r%d\n", process->number, params[0], params[1]);
		}
		else
		{
			addr = get_real_addr_of_ind(vm, process->next_instr,
															(short)params[1]);
			copy_val_at(vm, addr, (unsigned int)process->registres[params[0] - 1], 4);
			if (PRINT_INSTR)
				ft_printf("P%5d | st r%d %d\n", process->number, params[0], (short)params[1]);
			//dumpmemory(vm->memory);
		}
	}
	return (len);
}

int		op_add(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_sub(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_and(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_or(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_xor(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_zjmp(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_ldi(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_sti(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_fork(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_lld(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_lldi(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_lfork(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	(void)process;
	(void)params;
	(void)len;
	return (len);
}

int		op_aff(t_vm *vm, t_process *process, int *params, int len)
{
	int		param;

	(void)vm;
	param = params[0];
	if (param > 0 && param <= REG_NUMBER)
	{
		ft_putstr("Aff: ");
		write(1, &process->registres[param - 1], 1);
		ft_putchar('\n');
	}
	return (len);
}
