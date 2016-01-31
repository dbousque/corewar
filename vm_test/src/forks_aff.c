/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirkovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 12:24:39 by skirkovs          #+#    #+#             */
/*   Updated: 2016/01/31 12:31:55 by skirkovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

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
	if (!(fork = new_process(addr, vm->current_cycle -
								get_cycles_for_opcode(*process->next_instr))))
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
		ft_printf("P%5d | fork %d (%d)\n", process->number,
										(short)params[0], addr - vm->memory);
	ft_lstadd(&vm->processes, ft_lstnew(fork, sizeof(t_process)));
	return (len);
}

void	copy_state(t_process *fork, t_process *process)
{
	fork->carry = process->carry;
	fork->last_live = process->last_live;
	fork->nb_live = process->nb_live;
	fork->remaining_cycles = get_cycles_for_opcode(*fork->next_instr);
	fork->current_opcode = *fork->next_instr;
	if (fork->remaining_cycles > 0)
		fork->remaining_cycles--;
}

int		op_lfork(t_vm *vm, t_process *process, int *params, int len)
{
	t_process		*fork;
	unsigned char	*addr;

	addr = vm->memory + ((((short)params[0]) +
								(process->next_instr - vm->memory)) % MEM_SIZE);
	if (!(fork = new_process(addr, vm->current_cycle -
								get_cycles_for_opcode(*process->next_instr))))
		return (len);
	if (!(fork->registres = copy_regs(process->registres)))
		exit(1);
	copy_state(fork, process);
	if (PRINT_INSTR)
	{
		if ((short)params[0] < 0)
			ft_printf("P%5d | lfork %d (%d)\n", process->number,
										(short)params[0], addr - vm->memory);
		else
			ft_printf("P%5d | lfork %d (%d)\n", process->number,
				(short)params[0], (short)params[0] + addr - vm->memory - 2);
	}
	ft_lstadd(&vm->processes, ft_lstnew(fork, sizeof(t_process)));
	return (len);
}

int		op_aff(t_vm *vm, t_process *process, int *params, int len)
{
	int				param;
	int				val;

	(void)vm;
	param = params[0];
	if (PRINT_INSTR && param > 0 && param <= REG_NUMBER)
	{
		val = process->registres[param - 1] % 256;
		ft_putstr("Aff: ");
		write(1, &val, 1);
		ft_putchar('\n');
	}
	return (len);
}
