/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 16:53:18 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/29 18:34:50 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_pow(int nb, int pui)
{
	int		res;

	res = 1;
	while (pui > 0)
	{
		res = nb * res;
		pui--;
	}
	return (res);
}

void	parse_params2(unsigned char *str, int *to_read, unsigned int *final)
{
	int				j;
	int				k;
	int				m;
	int				i;
	unsigned int	res;
	int				total;

	i = 0;
	total = 0;
	while(to_read[i])
	{
		total = to_read[i] + total;
		i++;
	}
	k = 0;
	m = 0;
	j = 0;
	total--;
	while (to_read[j])
	{
		m = to_read[j];
		res = 0;
		k = 0;
		while (m > 0)
		{
			res = res + (unsigned char)str[total] * ft_pow(256, k);
			total--;
			m--;
			k++;
		}
		final[j] = res;
		j++;
	}
}

unsigned char	*next_byte_nb(t_vm *vm, unsigned char *byte, int nb)
{
	while (nb > 0)
	{
		if (byte < vm->memory + MEM_SIZE - 1)
			byte++;
		else
			byte = vm->memory;
		nb--;
	}
	return (byte);
}

void	parse_params(t_vm *vm, unsigned char *str, int *to_read, int *final, int nb)
{
	int				i;
	int				pow;
	int				res;

	i = 0;
	while (i < nb)
	{
		pow = to_read[i] - 1;
		res = 0;
		while (pow >= 0)
		{
			res += *(unsigned char*)next_byte_nb(vm, str, to_read[i] - 1 - pow)
															* ft_pow(256, pow);
			pow--;
		}
		str = next_byte_nb(vm, str, to_read[i]);
		final[i] = res;
		i++;
	}
}
