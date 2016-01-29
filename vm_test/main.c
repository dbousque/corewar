/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:58:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/29 17:37:48 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process	*new_process(unsigned char *start)
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
	res->nb_live = 0;
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

t_player	*get_player_from_file(t_vm *vm, char *content, int content_len)
{
	unsigned char	*file_content;
	t_player		*res;
	unsigned int	decal;

	decal = 4;
	file_content = (unsigned char*)content;
	if (!(res = (t_player*)malloc(sizeof(t_player))))
		return (NULL);
	res->number = vm->nb_players;
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
	/*if (decal + res->code_len != (unsigned int)content_len)
	{
		ft_printf("code_len : %d, decal : %d, content_len : %d\n", res->code_len, decal, content_len);
		ft_putendl_fd("Length not matching with actual length", 2);
		return (NULL);
	}*/
	if (!(res->code = (unsigned char*)malloc(sizeof(unsigned char) * (content_len - decal))))
		return (NULL);
	ft_memcpy(res->code, file_content + decal, content_len - decal);
	res->code_len = content_len - decal;
	res->start = NULL;
	return (res);
}

void	add_player_to_vm(t_vm *vm, t_player *player)
{
	(void)vm;
	//ft_printf("player name : %s\nplayer comment : %s\n player len : %u\n", player->name, player->comment, player->code_len);
	//print_memory(player->code, player->code_len);
	vm->players[player->number] = player;
}

void	dumpmemory(unsigned char *memory)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_putstr("         ");
		ft_printf("%02x ", memory[i]);
		i++;
		if (i % 64 == 0)
			ft_putstr("\n");
	}
}

void	load_players_in_memory(t_vm *vm)
{
	int		decal;
	int		offset;
	int		i;

	decal = MEM_SIZE / vm->nb_players;
	offset = 0;
	i = 0;
	while (i < vm->nb_players)
	{
		ft_memcpy(vm->memory + offset, vm->players[i]->code, vm->players[i]->code_len);
		vm->players[i]->start = vm->memory + offset;
		i++;
		offset += decal;
	}
}

t_vm	*init_vm(void)
{
	t_vm	*vm;

	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		return (NULL);
	if (!(vm->players = (t_player**)malloc(sizeof(t_player*) * (MAX_PLAYERS + 1))))
		return (NULL);
	vm->players[MAX_PLAYERS] = NULL;
	vm->processes = NULL;
	if (!(vm->memory = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE)))
		return (NULL);
	vm->nb_players = 0;
	vm->current_cycle = 0;
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

	tmp = ft_lstnew(new_process(vm->players[0]->start), sizeof(t_process));
	if (!tmp)
		return (0);
	ft_lstaddend(&vm->processes, tmp);
	((t_process*)vm->processes->content)->remaining_cycles = 
			get_cycles_for_opcode(*((t_process*)tmp->content)->next_instr);
	((t_process*)vm->processes->content)->registres[0] = 1;
	((t_process*)vm->processes->content)->carry = 0;
	tmp = ft_lstnew(new_process(vm->players[1]->start), sizeof(t_process));
	if (!tmp)
		return (0);
	ft_lstadd(&vm->processes, tmp);
	((t_process*)vm->processes->content)->remaining_cycles = 
			get_cycles_for_opcode(*((t_process*)tmp->content)->next_instr);
	((t_process*)vm->processes->content)->registres[0] = 2;
	((t_process*)vm->processes->content)->carry = 0;
	return (1);
}

char	one_process_living(t_vm *vm)
{
	t_list	*tmp;

	(void)vm;
	(void)tmp;
	return (1);
	/*if (vm->current_cycle == 0)
		return (1);
	tmp = vm->processes;
	while (tmp)
	{
		if (((t_process*)tmp->content)->nb_live > 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);*/
}

void	delete_dead_processes(t_vm *vm, int *to_die_iter, int *cycle_to_die, int *checks)
{
	t_list	*tmp;
	t_list	*parent;
	int		total_nb_live;

	total_nb_live = 0;
	parent = NULL;
	tmp = vm->processes;
	while (tmp)
	{
		if (((t_process*)tmp->content)->nb_live == 0)
		{
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
		ft_printf("Cycle to die is now %d\n", *cycle_to_die);
		*checks = MAX_CHECKS;
	}
	else
		(*checks)--;
	*to_die_iter = *cycle_to_die;
}

void	increment_next_instr(t_vm *vm, t_process *process, int nb)
{
	int		i;

	ft_printf("ADV %d (0x%04x -> 0x%04x) ", nb, process->next_instr - vm->memory, process->next_instr - vm->memory + nb);
	i = 0;
	while (i < nb)
	{
		ft_printf("%02x ", *(process->next_instr + i));
		i++;
	}
	ft_putchar('\n');
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

/*t_instruct	*new_instruct(t_process *process, unsigned char *param_byte)
{
	t_instruct	*res;

	if (!(res = (t_instruct*)malloc(sizeof(t_instruct))))
		return (NULL);
	res->start = process->next_instr;

}*/

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
	return (REG_SIZE);
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
		params_length[0] = get_length_of_type(opcode_descr, t_to_code(opcode_descr->params_types[0]));
	}
	else
	{
		decal = 6;
		i = 0;
		while (i < opcode_descr->nb_params)
		{
			params_length[i] = get_length_of_type(opcode_descr, (*param_byte >> decal) % 4);
			i++;
			decal -= 2;
		}
	}
}

int		add_lengths(int *params_length)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (params_length[i])
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

	opcode = *process->next_instr;
	opcode_descr = get_opcode_descr_with_opcode(opcode);
	if (!(params = (int*)malloc(sizeof(int) * opcode_descr->nb_params)))
		return (1);
	if (!(params_length = (int*)malloc(sizeof(int) * (opcode_descr->nb_params + 1))))
		return (1);
	params_length[opcode_descr->nb_params] = 0;
	get_params_length(params_length, opcode_descr, next_instr(vm, process->next_instr));
	parse_params(vm, next_instr(vm, next_instr(vm, process->next_instr)), params_length, params);
	return (opcode_descr->function(vm, process, params, add_lengths(params_length)));
}

int		execute_no_param_byte(t_vm *vm, t_process *process)
{
	int				opcode;
	t_op			*opcode_descr;
	int				*params;
	int				*params_length;

	opcode = *process->next_instr;
	opcode_descr = get_opcode_descr_with_opcode(opcode);
	if (!(params = (int*)malloc(sizeof(int) * opcode_descr->nb_params)))
		return (1);
	if (!(params_length = (int*)malloc(sizeof(int) * (opcode_descr->nb_params + 1))))
		return (1);
	params_length[opcode_descr->nb_params] = 0;
	get_params_length(params_length, opcode_descr, NULL);
	parse_params(vm, next_instr(vm, process->next_instr), params_length, params);
	return (opcode_descr->function(vm, process, params, add_lengths(params_length)));
}

char	opcode_is_not_zjmp(char opcode)
{
	int		i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (g_op_tab[i].opcode == opcode && ft_strcmp("zjmp", g_op_tab[i].name) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	execute_instruction(t_vm *vm, t_process *process)
{
	unsigned char	*opcode;
	int				len;
	char			is_not_zjmp;
	int				*params_length;
	t_op			*opcode_descr;

	opcode = process->next_instr;
	opcode_descr = get_opcode_descr_with_opcode(*opcode);
	is_not_zjmp = opcode_is_not_zjmp(*process->next_instr);
	if (opcode_has_param_byte(*process->next_instr))
	{
		if (!valid_param_byte(next_instr(vm, process->next_instr), *opcode))
		{
			if (!(params_length = (int*)malloc(sizeof(int) * (opcode_descr->nb_params + 1))))
				return ;
			get_params_length(params_length, opcode_descr, next_instr(vm, process->next_instr));
			increment_next_instr(vm, process, add_lengths(params_length));
			process->remaining_cycles = 
									get_cycles_for_opcode(*process->next_instr);
			return ;
		}
		len = execute_param_byte(vm, process);
		if (is_not_zjmp || len != 0)
			increment_next_instr(vm, process, len + 2);
		process->remaining_cycles = get_cycles_for_opcode(*process->next_instr);
		if (process->remaining_cycles > 0)
			process->remaining_cycles--;
	}
	else
	{
		len = execute_no_param_byte(vm, process);
		if (is_not_zjmp || len != 0)
			increment_next_instr(vm, process, len + 1);
		process->remaining_cycles = get_cycles_for_opcode(*process->next_instr);
		if (process->remaining_cycles > 0)
			process->remaining_cycles--;
	}
}

void	execute_processes(t_vm *vm)
{
	t_list	*tmp;

	tmp = vm->processes;
	while (tmp)
	{
		if (!valid_opcode(((t_process*)tmp->content)->next_instr))
			go_to_next_byte(vm, ((t_process*)tmp->content));
		else if (((t_process*)tmp->content)->remaining_cycles == 0)
			execute_instruction(vm, ((t_process*)tmp->content));
		else
			((t_process*)tmp->content)->remaining_cycles--;
		tmp = tmp->next;
	}
}

int		run_vm(t_vm *vm)
{
	int		cycle_to_die;
	int		to_die_iter;
	int		checks;


	cycle_to_die = CYCLE_TO_DIE;
	to_die_iter = cycle_to_die;
	checks = MAX_CHECKS;
	if (!(create_start_processes(vm)))
		return (0);
	while (one_process_living(vm))
	{
		if (to_die_iter <= 0)
			delete_dead_processes(vm, &to_die_iter, &cycle_to_die, &checks);
		if (!vm->processes)
			return (1);
		if (checks == 0)
		{
			cycle_to_die -= CYCLE_DELTA;
			ft_printf("Cycle to die is now %d\n", cycle_to_die);
			checks = MAX_CHECKS;
		}
		execute_processes(vm);
		vm->current_cycle++;
		to_die_iter--;
		ft_printf("It is now cycle %d\n", vm->current_cycle);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	char	*champion1;
	int		champ1_size;
	char	*champion2;
	int		champ2_size;
	t_vm	*vm;

	if (argc > 1)
	{
		champion1 = get_file_content(argv[1], &champ1_size);
		champion2 = get_file_content(argv[2], &champ2_size);
		if (!(vm = init_vm()))
			return (0);
		add_player_to_vm(vm, get_player_from_file(vm, champion1, champ1_size));
		add_player_to_vm(vm, get_player_from_file(vm, champion2, champ2_size));
		vm->players[2] = NULL;
		load_players_in_memory(vm);
		run_vm(vm);
		//dumpmemory(vm->memory);
	}
	return (0);
}
