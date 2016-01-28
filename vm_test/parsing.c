/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 16:53:18 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/28 18:30:03 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "vm.h"
#include <stdio.h>

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

void	parse_params(unsigned char *str, int *to_read, unsigned int *final)
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

int	main(void)
{
	unsigned char str[6] = {1,0,0,6,0,4};
	int to_read[4] = {2, 2, 2, 0};
	unsigned int final[3] = {0, 0, 0};
	parse_params(str, to_read, final);
	printf("%d\n", final[0]);
	printf("%d\n", final[1]);
	printf("%d\n", final[2]);
}
