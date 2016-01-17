/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 16:36:03 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/17 16:58:15 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_begin(char *tmp)
{
	char	*tmp2;
	{
		tmp2 = ft_strsub(tmp, 0, 5);
		if (ft_strcmp(tmp2, ".name") == 0)
		{
			tmp2 = ft_strsub(tmp, 5, ft_strlen(tmp) - 1);
			if (tmp2[0] == '"' && tmp2[ft_strlen(tmp) - 1] == '"')
				return (1);
			else
				return (0);
		}
		tmp2 = ft_strsub(tmp, 0, 8);
		if (ft_strcmp(tmp2, ".comment") == 0)
		{
			tmp2 = ft_strsub(tmp, 8, ft_strlen(tmp) - 1);
			if (tmp2[0] == '"' && tmp2[ft_strlen(tmp) - 1] == '"')
				return (2);
			else
				return (0);
		}
	}
}

int		check_line(char *line)
{
	int		begin;
	int		previous;
	char	*tmp;

	tmp = ft_strtrim(line);
	if (tmp[0] == '.')
		return (check_begin);
	else
	{
	}
}

void	add_command(int test, t_function **file)
{
}
