/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:58:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/30 17:00:46 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process	*new_process(unsigned char *start, int cycle_creation)
{
	static int	nb = 1;
	t_process	*res;

	if (!(res = (t_process*)malloc(sizeof(t_process))))
		return (NULL);
	if (!(res->registres = (int*)malloc(sizeof(int) * REG_NUMBER)))
		return (NULL);
	res->next_instr = start;
	res->number = nb;
	nb++;
	res->carry = 0;
	res->remaining_cycles = 0;
	res->last_live = 0;
	res->creation_cycle = cycle_creation;
	res->nb_live = 0;
	res->current_opcode = *start;
	return (res);
}

char	*get_file_content(char *filename, int *res_size)
{
	char	*res;
	char	buf[1024];
	int		fd;
	int		size;
	int		ret;
	int		decal;
	int		i;

	fd = open(filename, O_RDONLY);
	size = 0;
	while ((ret = read(fd, buf, 1024)) > 0)
	{
		i = 0;
		while (buf[i])
		{
			ft_putnbr(buf[i]);
			i++;
		}
		size += ret;
	}
	res = (char*)malloc(sizeof(char) * size);
	close(fd);
	decal = 0;
	fd = open(filename, O_RDONLY);
	while ((ret = read(fd, res + decal, 1024)) > 0)
		decal += ret;
	*res_size = size;
	return (res);
}

unsigned int	get_value_big_endian(unsigned int val)
{
	unsigned int	res;

	res = 0;
	res = (*(unsigned char*)&val) * 256 * 256 * 256;
	res += (*(unsigned char*)&val + 1) * 256 * 256;
	res += (*(unsigned char*)&val + 2) * 256;
	res += (*(unsigned char*)&val + 3);
	return (res);
}

t_player	*get_player_from_file(t_vm *vm, char *content, int content_len, int number)
{
	unsigned char	*file_content;
	t_player		*res;
	unsigned int	decal;

	decal = 4;
	file_content = (unsigned char*)content;
	if (!(res = (t_player*)malloc(sizeof(t_player))))
		return (NULL);
	res->number = number;
	vm->nb_players++;
	if (!(res->name = (char*)malloc(sizeof(char) * (PROG_NAME_LENGTH + 1))))
		return (NULL);
	res->name[PROG_NAME_LENGTH] = '\0';
	ft_memcpy(res->name, content + decal, PROG_NAME_LENGTH);
	decal += PROG_NAME_LENGTH;
	//res->code_len = get_value_big_endian(*(unsigned int*)file_content);
	decal += sizeof(unsigned int);
	if (!(res->comment = (char*)malloc(sizeof(char) * (COMMENT_LENGTH + 1))))
		return (NULL);
	res->comment[COMMENT_LENGTH] = '\0';
	ft_memcpy(res->comment, content + decal, COMMENT_LENGTH);
	decal += COMMENT_LENGTH;
	if (!(res->code = (unsigned char*)malloc(sizeof(unsigned char) * (content_len - decal))))
		return (NULL);
	ft_memcpy(res->code, file_content + decal, content_len - decal);
	res->code_len = content_len - decal;
	res->start = NULL;
	return (res);
}

void	add_player_to_vm(t_vm *vm, t_player *player)
{
	static int	index = 0;

	vm->players[index] = player;
	index++;
}

void	dumpmemory(unsigned char *memory)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", memory[i]);
		i++;
		if (i % 64 == 0)
			ft_putstr("\n");
	}
	exit(1);
}

void	load_players_in_memory(t_vm *vm)
{
	int		decal;
	int		offset;
	int		i;

	ft_putendl("Introducing contestants...");
	decal = MEM_SIZE / vm->nb_players;
	offset = 0;
	i = 0;
	while (i < vm->nb_players)
	{
		ft_memcpy(vm->memory + offset, vm->players[i]->code,
													vm->players[i]->code_len);
		vm->players[i]->start = vm->memory + offset;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
	vm->players[i]->code_len, vm->players[i]->name, vm->players[i]->comment);
		i++;
		offset += decal;
	}
}

t_vm	*init_vm(void)
{
	t_vm	*vm;

	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (NULL);
	if (!(vm->players = (t_player**)malloc(sizeof(t_player*)
														* (MAX_PLAYERS + 1))))
		return (NULL);
	vm->players[MAX_PLAYERS] = NULL;
	vm->processes = NULL;
	if (!(vm->memory = (unsigned char*)malloc(sizeof(unsigned char)
																* MEM_SIZE)))
		return (NULL);
	vm->nb_players = 0;
	vm->current_cycle = 0;
	vm->last_verif = 0;
	vm->last_player = 0;
	return (vm);
}

int		get_cycles_for_opcode(int opcode)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (g_op_tab[i].opcode == opcode)
			return (g_op_tab[i].nb_cycles);
		i++;
	}
	return (0);
}

int		create_start_processes(t_vm *vm)
{
	t_list	*tmp;

	tmp = ft_lstnew(new_process(vm->players[0]->start, 0), sizeof(t_process));
	if (!tmp)
		return (0);
	ft_lstaddend(&vm->processes, tmp);
	((t_process*)vm->processes->content)->remaining_cycles = 
			get_cycles_for_opcode(*((t_process*)tmp->content)->next_instr);
	((t_process*)vm->processes->content)->registres[0] = vm->players[0]->number;
	((t_process*)vm->processes->content)->carry = 0;
	tmp = ft_lstnew(new_process(vm->players[1]->start, 0), sizeof(t_process));
	if (!tmp)
		return (0);
	ft_lstadd(&vm->processes, tmp);
	((t_process*)vm->processes->content)->remaining_cycles = 
			get_cycles_for_opcode(*((t_process*)tmp->content)->next_instr);
	((t_process*)vm->processes->content)->registres[0] = vm->players[1]->number;
	((t_process*)vm->processes->content)->carry = 0;
	return (1);
}

void	delete_dead_processes(t_vm *vm, int *to_die_iter, int *cycle_to_die, int *checks)
{
	t_list		*tmp;
	t_list		*parent;
	int			total_nb_live;
	t_process	*proc;

	total_nb_live = 0;
	parent = NULL;
	tmp = vm->processes;
	while (tmp)
	{
		proc = ((t_process*)tmp->content);
		if (proc->nb_live == 0)
		{
			if (PRINT_INSTR)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
									proc->number, vm->current_cycle -
(proc->last_live > 0 ? proc->last_live : proc->creation_cycle), *cycle_to_die);
			if (parent)
				parent->next = tmp->next;
			else
				vm->processes = tmp->next;
		}
		else
		{
			total_nb_live += ((t_process*)tmp->content)->nb_live;
			((t_process*)tmp->content)->nb_live = 0;
			parent = tmp;
		}
		tmp = tmp->next;
	}
	if (total_nb_live >= NBR_LIVE)
	{
		*cycle_to_die -= CYCLE_DELTA;
		if (PRINT_INSTR)
			ft_printf("Cycle to die is now %d\n", *cycle_to_die);
		*checks = MAX_CHECKS;
	}
	else
		(*checks)--;
	vm->last_verif = vm->current_cycle;
	*to_die_iter = *cycle_to_die;
}

void	increment_next_instr(t_vm *vm, t_process *process, int nb)
{
	int				i;
	unsigned char	*addr;

	if (PRINT_INSTR)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", nb,
	process->next_instr - vm->memory, process->next_instr - vm->memory + nb);
		i = 0;
		addr = process->next_instr;
		while (i < nb)
		{
			ft_printf("%02x ", *addr);
			addr = next_instr(vm, addr);
			i++;
		}
		ft_putchar('\n');
	}
	while (nb > 0)
	{
		if (process->next_instr < vm->memory + MEM_SIZE - 1)
			process->next_instr++;
		else
			process->next_instr = vm->memory;
		nb--;
	}
}

void	go_to_next_byte(t_vm *vm, t_process *process)
{
	if (process->next_instr < vm->memory + MEM_SIZE - 1)
		process->next_instr++;
	else
		process->next_instr = vm->memory;
	process->remaining_cycles = get_cycles_for_opcode(*process->next_instr);
	process->current_opcode = *process->next_instr;
	if (process->remaining_cycles > 0)
		process->remaining_cycles--;
}

char	valid_opcode(unsigned char *opcode)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (*opcode == g_op_tab[i].opcode)
			return (1);
		i++;
	}
	return (0);
}

char	opcode_has_param_byte(unsigned char opcode)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (g_op_tab[i].opcode == opcode)
			return (g_op_tab[i].has_param_byte);
		i++;
	}
	ft_putendl_fd("BIG ERROR !", 2);
	return (0);
}

t_op	*get_opcode_descr_with_opcode(unsigned char opcode)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (g_op_tab[i].opcode == opcode)
			return (&g_op_tab[i]);
		i++;
	}
	ft_putendl_fd("BIG ERROR !", 2);
	return (NULL);
}

int		is_in_tab(int a, int *tab, int i)
{
	if (tab[i] & a)
		return (1);
	return (0);
}

char	valid_param_byte(unsigned char *param_byte, unsigned char opcode)
{
	t_op			*opcode_descr;
	int				decal;
	int				i;
	unsigned char	a;

	opcode_descr = get_opcode_descr_with_opcode(opcode);
	decal = 6;
	i = 0;
	while (i < opcode_descr->nb_params)
	{
		a = (*param_byte >> decal) % 4;
		if (a == REG_CODE)
			a = T_REG;
		else if (a == DIR_CODE)
			a = T_DIR;
		else if (a == IND_CODE)
			a = T_IND;
		if (!is_in_tab(a, opcode_descr->params_types, i))
			return (0);
		decal -= 2;
		i++;
	}
	return (1);
}

unsigned char	*next_instr(t_vm *vm, unsigned char *current_instr)
{
	if (current_instr < vm->memory + MEM_SIZE - 1)
		return (current_instr + 1);
	return (vm->memory);
}

int		get_length_of_type(t_op *opcode_descr, unsigned char type)
{
	if (type == DIR_CODE)
	{
		if (opcode_descr->small_dir)
			return (DIR_SIZE / 2);
		return (DIR_SIZE);
	}
	if (type == IND_CODE)
		return (IND_SIZE);
	else if (type == REG_CODE)
		return (REG_SIZE);
	return (0);
}

unsigned char	t_to_code(unsigned char t)
{
	if (t == T_REG)
		return (REG_CODE);
	if (t == T_IND)
		return (IND_CODE);
	return (DIR_CODE);
}

void	get_params_length(int *params_length, t_op *opcode_descr,
													unsigned char *param_byte)
{
	int		decal;
	int		i;

	if (!param_byte)
	{
		params_length[0] = get_length_of_type(opcode_descr,
									t_to_code(opcode_descr->params_types[0]));
	}
	else
	{
		decal = 6;
		i = 0;
		while (i < opcode_descr->nb_params)
		{
			params_length[i] = get_length_of_type(opcode_descr,
												(*param_byte >> decal) % 4);
			i++;
			decal -= 2;
		}
	}
}

int		add_lengths(int *params_length, int nb)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (i < nb)
	{
		len += params_length[i];
		i++;
	}
	return (len);
}

int		execute_param_byte(t_vm *vm, t_process *process)
{
	int				opcode;
	t_op			*opcode_descr;
	int				*params;
	int				*params_length;

	opcode = process->current_opcode;
	opcode_descr = get_opcode_descr_with_opcode(opcode);
	if (!(params = (int*)malloc(sizeof(int) * opcode_descr->nb_params)))
		return (1);
	if (!(params_length = (int*)malloc(sizeof(int) * opcode_descr->nb_params)))
		return (1);
	get_params_length(params_length, opcode_descr, next_instr(vm,
														process->next_instr));
	parse_params(vm, next_instr(vm, next_instr(vm, process->next_instr)),
								params_length, params, opcode_descr->nb_params);
	return (opcode_descr->function(vm, process, params,
						add_lengths(params_length, opcode_descr->nb_params)));
}

int		execute_no_param_byte(t_vm *vm, t_process *process)
{
	int				opcode;
	t_op			*opcode_descr;
	int				*params;
	int				*params_length;

	opcode = process->current_opcode;
	opcode_descr = get_opcode_descr_with_opcode(opcode);
	if (!(params = (int*)malloc(sizeof(int) * opcode_descr->nb_params)))
		return (1);
	if (!(params_length = (int*)malloc(sizeof(int) * opcode_descr->nb_params)))
		return (1);
	get_params_length(params_length, opcode_descr, NULL);
	parse_params(vm, next_instr(vm, process->next_instr), params_length, params,
													opcode_descr->nb_params);
	return (opcode_descr->function(vm, process, params,
						add_lengths(params_length, opcode_descr->nb_params)));
}

char	opcode_is_not_zjmp(char opcode)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (g_op_tab[i].opcode == opcode
			&& ft_strcmp("zjmp", g_op_tab[i].name) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	handle_invalid_param_byte(t_vm *vm, t_process *process,
														unsigned char *opcode)
{
	int				*params_length;
	t_op			*opcode_descr;

	opcode_descr = get_opcode_descr_with_opcode(*opcode);
	if (!(params_length = (int*)malloc(sizeof(int) * opcode_descr->nb_params)))
		return ;
	get_params_length(params_length, opcode_descr, next_instr(vm,
														process->next_instr));
	increment_next_instr(vm, process, add_lengths(params_length,
												opcode_descr->nb_params) + 2);
	process->remaining_cycles = get_cycles_for_opcode(*process->next_instr);
	process->current_opcode = *process->next_instr;
	if (process->remaining_cycles > 0)
		process->remaining_cycles--;
}

void	execute_instruction(t_vm *vm, t_process *process)
{
	unsigned char	*opcode;
	int				len;
	char			is_not_zjmp;

	opcode = &process->current_opcode;
	is_not_zjmp = opcode_is_not_zjmp(process->current_opcode);
	if (opcode_has_param_byte(process->current_opcode))
	{
		if (!valid_param_byte(next_instr(vm, process->next_instr), *opcode))
			return (handle_invalid_param_byte(vm, process, opcode));
		len = execute_param_byte(vm, process);
		if (is_not_zjmp || len != 0)
			increment_next_instr(vm, process, len + 2);
	}
	else
	{
		len = execute_no_param_byte(vm, process);
		if (is_not_zjmp || len != 0)
			increment_next_instr(vm, process, len + 1);
	}
	process->remaining_cycles = get_cycles_for_opcode(*process->next_instr);
	process->current_opcode = *process->next_instr;
	if (process->remaining_cycles > 0)
		process->remaining_cycles--;
}

void	update_instructions(t_vm *vm)
{
	t_list		*tmp;
	t_process	*process;

	tmp = vm->processes;
	while (tmp)
	{
		process = ((t_process*)tmp->content);
		if ((valid_opcode(&process->current_opcode)
			&& get_cycles_for_opcode(process->current_opcode) ==
			process->remaining_cycles + 1 && valid_opcode(process->next_instr))
			|| (process->remaining_cycles == 0
				&& !valid_opcode(&process->current_opcode)))
		{
			process->current_opcode = *process->next_instr;
			process->remaining_cycles =
									get_cycles_for_opcode(*process->next_instr);
			if (process->remaining_cycles > 0)
				process->remaining_cycles--;
		}
		tmp = tmp->next;
	}
}

void	execute_processes(t_vm *vm)
{
	t_list		*tmp;

	tmp = vm->processes;
	while (tmp)
	{
		if (!valid_opcode(&((t_process*)tmp->content)->current_opcode))
			go_to_next_byte(vm, ((t_process*)tmp->content));
		else if (((t_process*)tmp->content)->remaining_cycles == 0)
			execute_instruction(vm, ((t_process*)tmp->content));
		else
			((t_process*)tmp->content)->remaining_cycles--;
		tmp = tmp->next;
	}
	update_instructions(vm);
}

void	decrement_cycle_to_die(int *cycle_to_die, int *to_die_iter, int *checks)
{
	*cycle_to_die -= CYCLE_DELTA;
	*to_die_iter -= CYCLE_DELTA;
	if (PRINT_INSTR)
		ft_printf("Cycle to die is now %d\n", *cycle_to_die);
	*checks = MAX_CHECKS;
}

void	init_vars(int *cycle_to_die, int *to_die_iter, int *checks)
{
	*cycle_to_die = CYCLE_TO_DIE;
	*to_die_iter = *cycle_to_die;
	*checks = MAX_CHECKS;
}

int		run_vm(t_vm *vm, int dump)
{
	int		cycle_to_die;
	int		to_die_iter;
	int		checks;

	init_vars(&cycle_to_die, &to_die_iter, &checks);
	if (!(create_start_processes(vm)))
		return (0);
	while (1)
	{
		execute_processes(vm);
		if (to_die_iter <= 0)
			delete_dead_processes(vm, &to_die_iter, &cycle_to_die, &checks);
		if (!vm->processes)
			return (1);
		if (checks == 0)
			decrement_cycle_to_die(&cycle_to_die, &to_die_iter, &checks);
		if (vm->current_cycle == dump)
			dumpmemory(vm->memory);
		vm->current_cycle++;
		to_die_iter--;
		if (PRINT_INSTR)
			ft_printf("It is now cycle %d\n", vm->current_cycle);
	}
	return (1);
}

t_player	*get_player_with_number(t_vm *vm, int numb)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->players[i]->number == numb)
			return (vm->players[i]);
		i++;
	}
	ft_putendl_fd("BIG ERROR !\n", 2);
	return (NULL);
}

void	print_winner(t_vm *vm)
{
	t_player	*player;

	player = get_player_with_number(vm, vm->last_player);
	ft_printf("Contestant %d, \"%s\", has won !\n", -player->number,
																player->name);
}

int		main(int argc, char **argv)
{
	char	*champion1;
	int		champ1_size;
	char	*champion2;
	int		champ2_size;
	t_vm	*vm;
	int		dump;

	if (argc > 1)
	{
		dump = -1;
		if (argc > 3)
			dump = ft_atoi(argv[3]);
		champion1 = get_file_content(argv[1], &champ1_size);
		champion2 = get_file_content(argv[2], &champ2_size);
		if (!(vm = init_vm()))
			return (0);
		add_player_to_vm(vm, get_player_from_file(vm, champion1, champ1_size, -1));
		add_player_to_vm(vm, get_player_from_file(vm, champion2, champ2_size, -2));
		vm->players[2] = NULL;
		vm->last_player = -2;
		load_players_in_memory(vm);
		run_vm(vm, dump);
		print_winner(vm);
	}
	return (0);
}
