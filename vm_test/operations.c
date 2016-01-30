/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 18:03:28 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/30 15:45:46 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*valid_player(t_vm *vm, int dir_val)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (dir_val == vm->players[i]->number)
			return (vm->players[i]);
		i++;
	}
	return (NULL);
}

int		type_of_n_param(t_vm *vm, t_process *process, int n)
{
	unsigned char	type;

	type = (*next_instr(vm, process->next_instr) >> (6 - (n * 2))) & 3;
	return (type);
}

unsigned char	*get_real_addr_of_ind(t_vm *vm, unsigned char *ori_addr,
														int to_add, char modulo)
{
	unsigned char	*addr;

	if (modulo)
		addr = ori_addr + (to_add % IDX_MOD);
	else
		addr = ori_addr + to_add;
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
		*(get_real_addr_of_ind(vm, addr, i, 1)) = val / ft_pow(256, nb - i - 1);
		val -= (val / ft_pow(256, nb - i - 1)) * ft_pow(256, nb - i - 1);
		i++;
	}
}

char	*get_name_of_opcode(char opcode)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (g_op_tab[i].opcode == opcode)
			return (g_op_tab[i].name);
		i++;
	}
	ft_putendl_fd("BIG ERROR\n", 2);
	return ("");
}

char	valid_reg(int param)
{
	if (param > 0 && param <= 16)
		return (1);
	return (0);
}

int		op_live(t_vm *vm, t_process *process, int *params, int len)
{
	int			dir_val;
	t_player	*play;

	dir_val = params[0];
	if (PRINT_INSTR)
		ft_printf("P%5d | live %d\n", process->number, dir_val);
	process->last_live = vm->current_cycle;
	process->nb_live++;
	if ((play = valid_player(vm, dir_val)))
	{
		vm->last_player = dir_val;
		if (PRINT_INSTR)
			ft_printf("Player %d (%s) is said to be alive\n", -dir_val, play->name);
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
															(short)params[0], 1);
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
															(short)params[1], 1);
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
	if (valid_reg(params[0]) && valid_reg(params[1]) && valid_reg(params[2]))
	{
		if (PRINT_INSTR)
			ft_printf("P%5d | add r%d r%d r%d\n", process->number,
											params[0], params[1], params[2]);
		process->registres[params[2] - 1] = process->registres[params[0] - 1]
											+ process->registres[params[1] - 1];
		if (process->registres[params[2] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	return (len);
}

int		op_sub(t_vm *vm, t_process *process, int *params, int len)
{
	(void)vm;
	if (valid_reg(params[0]) && valid_reg(params[1]) && valid_reg(params[2]))
	{
		if (PRINT_INSTR)
			ft_printf("P%5d | sub r%d r%d r%d\n", process->number,
											params[0], params[1], params[2]);
		process->registres[params[2] - 1] = process->registres[params[0] - 1]
											- process->registres[params[1] - 1];
		if (process->registres[params[2] - 1] == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	ft_printf("LEN : %d\n", len);
	return (len);
}

int		get_val_of_n_param(t_vm *vm, t_process *process, int *params, int n, int *error)
{
	int				val;
	unsigned char	*addr;
	char			type;

	if ((type = type_of_n_param(vm, process, n)) == IND_CODE)
	{
		addr = get_real_addr_of_ind(vm, process->next_instr, (short)params[n], 1);
		val = get_val_at(vm, addr, 4);
	}
	else if (type == REG_CODE)
	{
		if (!valid_reg(params[n]))
		{
			*error = 1;
			return (0);
		}
		val = process->registres[params[n] - 1];
	}
	else
		val = (short)params[n];
	return (val);
}

char	*print_val(int val, int is_reg)
{
	if (is_reg)
		return ft_strjoin("r", ft_itoa(val));
	return ft_itoa(val);
}

int		op_and_or_xor(t_vm *vm, t_process *process, int *params, char sign)
{
	int				val1;
	int				val2;
	int				error;

	error = 0;
	process->carry = 0;
	if (!valid_reg(params[2]))
		return (0);
	val1 = get_val_of_n_param(vm, process, params, 0, &error);
	if (error)
		return (0);
	val2 = get_val_of_n_param(vm, process, params, 1, &error);
	if (error)
		return (0);
	process->carry = 1;
	if (sign == '&')
		process->registres[params[2] - 1] = val1 & val2;
	else if (sign == '|')
		process->registres[params[2] - 1] = val1 | val2;
	else if (sign == '^')
		process->registres[params[2] - 1] = val1 ^ val2;
	if (PRINT_INSTR)
	{
		ft_printf("P%5d | %s %s %s r%d\n", process->number, get_name_of_opcode(*process->next_instr), print_val(val1, 0), print_val(val2, 0), params[2]);
	}
	if (process->registres[params[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (1);
}

int		op_and(t_vm *vm, t_process *process, int *params, int len)
{
	op_and_or_xor(vm, process, params, '&');
	return (len);
}

int		op_or(t_vm *vm, t_process *process, int *params, int len)
{
	op_and_or_xor(vm, process, params, '|');
	return (len);
}

int		op_xor(t_vm *vm, t_process *process, int *params, int len)
{
	op_and_or_xor(vm, process, params, '^');
	return (len);
}

int		op_zjmp(t_vm *vm, t_process *process, int *params, int len)
{
	if (process->carry == 1)
	{
		if (PRINT_INSTR)
			ft_printf("P%5d | zjmp %d OK\n", process->number, (short)params[0]);
		process->next_instr = get_real_addr_of_ind(vm, process->next_instr,
														(short)params[0], 1);
		process->remaining_cycles = get_cycles_for_opcode(*process->next_instr);
		if (process->remaining_cycles > 0)
			process->remaining_cycles--;
		return (0);
	}
	ft_printf("P%5d | zjmp %d FAILED\n", process->number, (short)params[0]);
	return (len);
}	

int		op_ldi(t_vm *vm, t_process *process, int *params, int len)
{
	int		val1;
	int		val2;
	int		res;
	int		error;

	if (valid_reg(params[2]))
	{
		error = 0;
		val1 = get_val_of_n_param(vm, process, params, 0, &error);
		if (error)
			return (len);
		val2 = get_val_of_n_param(vm, process, params, 1, &error);
		if (error)
			return (len);
		res = get_val_at(vm, get_real_addr_of_ind(vm, process->next_instr, val1 + val2, 1), REG_SIZE);
		process->registres[params[2] - 1] = res;
		if (PRINT_INSTR)
		{
			ft_printf("%08b\n", *next_instr(vm, process->next_instr));
			ft_printf("P%5d | ldi %s %s %s\n", process->number, print_val(val1, type_of_n_param(vm, process, 0) == REG_CODE), print_val(val2, type_of_n_param(vm, process, 1) == REG_CODE), print_val(params[2], 1));
		}
	}
	return (len);
}

int		op_sti(t_vm *vm, t_process *process, int *params, int len)
{
	unsigned char	*addr;
	int				val1;
	int				val2;
	int				error;

	if (valid_reg(params[0]))
	{
		error = 0;
		val1 = get_val_of_n_param(vm, process, params, 1, &error);
		if (error)
			return (len);
		val2 = get_val_of_n_param(vm, process, params, 2, &error);
		if (error)
			return (len);
		//addr = get_real_addr_of_ind(vm, process->next_instr, val1 + val2, 1);
		addr = vm->memory + (((val1 + val2) % IDX_MOD) + (process->next_instr - vm->memory)) % MEM_SIZE;
		copy_val_at(vm, addr, (unsigned int)process->registres[params[0] - 1], 4);
		if (PRINT_INSTR)
		{
			ft_printf("P%5d | sti %s %s %s\n", process->number, print_val(params[0], 1), print_val(val1, type_of_n_param(vm, process, 1) == REG_CODE), print_val(val2, type_of_n_param(vm, process, 2) == REG_CODE));
			ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", val1, val2, val1 + val2, (((val1 + val2) % IDX_MOD) + (process->next_instr - vm->memory)) % MEM_SIZE);
		}
		//dumpmemory(vm->memory);
	}
	return (len);
}

int		*copy_regs(int *registres)
{
	int		*res;
	int		i;

	if (!(res = (int*)malloc(sizeof(int) * REG_NUMBER)))
		return (NULL);
	i = 0;
	while (i < REG_NUMBER)
	{
		res[i] = registres[i];
		i++;
	}
	return (res);
}

int		op_fork(t_vm *vm, t_process *process, int *params, int len)
{
	t_process		*fork;
	unsigned char	*addr;

	addr = get_real_addr_of_ind(vm, process->next_instr, (short)params[0], 1);
	if (!(fork = new_process(addr, vm->current_cycle - get_cycles_for_opcode(*process->next_instr))))
		return (len);
	fork->carry = process->carry;
	if (!(fork->registres = copy_regs(process->registres)))
		exit(1);
	fork->last_live = process->last_live;
	fork->nb_live = process->nb_live;
	fork->remaining_cycles = get_cycles_for_opcode(*fork->next_instr);
	fork->current_opcode = *fork->next_instr;
	if (fork->remaining_cycles > 0)
		fork->remaining_cycles--;
	if (PRINT_INSTR)
		ft_printf("P%5d | fork %d (%d)\n", process->number, (short)params[0], addr - vm->memory);
	ft_lstadd(&vm->processes, ft_lstnew(fork, sizeof(t_process)));
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
	int		error;

	if (valid_reg(params[2]))
	{
		error = 0;
		val1 = get_val_of_n_param(vm, process, params, 0, &error);
		if (error)
			return (len);
		val2 = get_val_of_n_param(vm, process, params, 1, &error);
		if (error)
			return (len);
		res = get_val_at(vm, get_real_addr_of_ind(vm, process->next_instr, val1 + val2, 1), REG_SIZE);
		process->registres[params[2] - 1] = res;
		if (val1 + val2 == 0)
			process->carry = 1;
		else
			process->carry = 0;
		if (PRINT_INSTR)
		{
			ft_printf("P%5d | lldi %s %s %s\n", process->number, print_val(val1, type_of_n_param(vm, process, 0) == REG_CODE), print_val(val2, type_of_n_param(vm, process, 1) == REG_CODE), print_val(params[2], 1));
		}
	}
	return (len);
}

int		op_lfork(t_vm *vm, t_process *process, int *params, int len)
{
	t_process		*fork;
	unsigned char	*addr;

	//addr = get_real_addr_of_ind(vm, process->next_instr, (short)params[0], 0);
	addr = vm->memory + ((((short)params[0]) + (process->next_instr - vm->memory)) % MEM_SIZE);
	if (!(fork = new_process(addr, vm->current_cycle - get_cycles_for_opcode(*process->next_instr))))
		return (len);
	fork->carry = process->carry;
	if (!(fork->registres = copy_regs(process->registres)))
		exit(1);
	fork->last_live = process->last_live;
	fork->nb_live = process->nb_live;
	fork->remaining_cycles = get_cycles_for_opcode(*fork->next_instr);
	fork->current_opcode = *fork->next_instr;
	if (fork->remaining_cycles > 0)
		fork->remaining_cycles--;
	if (PRINT_INSTR)
	{
		if ((short)params[0] + (addr - vm->memory) < MEM_SIZE)
			ft_printf("P%5d | lfork %d (%d)\n", process->number, (short)params[0], addr - vm->memory);
		else
			ft_printf("P%5d | lfork %d (%d)\n", process->number, (short)params[0], (short)params[0] + addr - vm->memory - 2);
	}
	ft_lstadd(&vm->processes, ft_lstnew(fork, sizeof(t_process)));
	return (len);
}

int		absolute(int val)
{
	if (val < 0)
		return (-val);
	return (val);
}

int		op_aff(t_vm *vm, t_process *process, int *params, int len)
{
	int				param;
	int				val;

	(void)vm;
	param = params[0];
	if (param > 0 && param <= REG_NUMBER)
	{
		val = process->registres[param - 1] % 256;
		ft_putstr("Aff: ");
		write(1, &val, 1);
		ft_putchar('\n');
	}
	return (len);
}
