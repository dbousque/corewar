/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:58:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/27 19:25:19 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

typedef struct		s_player
{
	char			*name;
	char			*comment;
	int				number;
	unsigned char	*code;
	unsigned int	code_len;
	unsigned char	*start;
}					t_player;

typedef struct		s_param
{
	char			type;
	long long		value;
}					t_param;

typedef struct		s_instruct
{
	unsigned char	*start;
	int				len;
	int				opcode;
	t_param			*params;
}					t_instruct;

typedef struct		s_process
{
	int				number;
	int				*registres;
	unsigned char	*next_instr;
	char			carry;
	int				remaining_cycles;
	int				last_live;
	int				nb_live;
}					t_process;

typedef struct		s_vm
{
	t_player		**players;
	int				nb_players;
	t_list			*processes;
	unsigned char	*memory;
	int				current_cycle;
}					t_vm;

t_process	*new_process(unsigned char *start)
{
	static int	nb = 0;
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
	tmp = ft_lstnew(new_process(vm->players[1]->start), sizeof(t_process));
	if (!tmp)
		return (0);
	ft_lstadd(&vm->processes, tmp);
	((t_process*)vm->processes->content)->remaining_cycles = 
			get_cycles_for_opcode(*((t_process*)tmp->content)->next_instr);
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
		*cycle_to_die -= CYCLE_DELTA;
	*to_die_iter = *cycle_to_die;
	*checks = MAX_CHECKS;
}

void	increment_next_instr(t_vm *vm, t_process *process)
{
	if (process->next_instr < vm->memory + MEM_SIZE - 1)
		process->next_instr++;
	else
		process->next_instr = vm->memory;
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

void	execute_instruction(t_vm *vm, t_process *process)
{
	if (!valid_opcode(process->next_instr))
		increment_next_instr(vm, process);
	else
	{
		if (opcode_has_param_byte(*process->next_instr))
		{
			increment_next_instr(vm, process);
			if (!valid_param_byte(process->next_instr + 1))
		}	
	}
}

void	execute_processes(t_vm *vm)
{
	t_list	*tmp;

	tmp = vm->processes;
	while (tmp)
	{
		if (((t_process*)tmp->content)->remaining_cycles == 0)
		{
			execute_instruction(vm, ((t_process*)tmp->content));
		}
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
			checks = MAX_CHECKS;
		}
		execute_processes(vm);
		vm->current_cycle++;
		to_die_iter--;
		checks--;
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
		dumpmemory(vm->memory);
		run_vm(vm);
	}
	return (0);
}
