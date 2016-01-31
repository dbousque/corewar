/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ninth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 15:44:35 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/31 16:47:51 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <limits.h>

int		validate(int number, t_vm *vm, int *current_num)
{
	int		i;
	int		max;
	int		ok;

	ok = 0;
	i = -1;
	max = INT_MIN;
	while (++i < vm->nb_players)
	{
		if (vm->players[i]->number == number)
			ok = 0;
		if (vm->players[i]->number > max)
			max = vm->players[i]->number;
	}
	if (ok)
		*current_num = max;
	return (ok ? number : max);
}

void	parse_args(int argc, char **argv, t_vm *vm, int *dump)
{
	int		i;
	int		current_num;
	size_t	number;
	int		players;

	players = 0;
	current_num = -1;
	number = (size_t)INT_MAX + 1;
	i = 0;
	while (++i < argc)
	{
		if (ft_strcmp(argv[i], "-dump") == 0)
		{
			if (++i == argc)
				exit(write(2, "Bad params\n", ft_strlen("Bad params\n")));
			*dump = get_num(argv[i], 0);
		}
		else if (ft_strcmp(argv[i], "-n") == 0)
		{
			number = validate(number, vm, &current_num);
			if (++i == argc)
				exit(write(2, "Bad params\n", ft_strlen("Bad params\n")));
			number = get_num(argv[i], 1);
			if (++i == argc)
				exit(write(2, "Bad params\n", ft_strlen("Bad params\n")));
			add_champion(argv[i], vm, number);
		}
		else
			add_champion(argv[i], vm, current_num--);
	}
}

void	free_vm(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_players)
	{
		free(vm->players[i]->name);
		free(vm->players[i]->comment);
		free(vm->players[i]->code);
		free(vm->players[i]);
		i++;
	}
	free(vm->memory);
	free(vm);
}

int		main(int argc, char **argv)
{
	t_vm	*vm;
	int		dump;

	if (argc > 1)
	{
		if (!(vm = init_vm()))
			exit(write(2, "No memory\n", 10));
		dump = -1;
		parse_args(argc, argv, vm, &dump);
		if (vm->nb_players < 1)
			exit(write(2, "No players\n", 11));
		vm->last_player = vm->players[vm->nb_players - 1]->number;
		load_players_in_memory(vm);
		run_vm(vm, dump);
		print_winner(vm);
		free_vm(vm);
	}
	return (0);
}
