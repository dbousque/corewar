/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 18:03:47 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/17 19:15:38 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		check_params(char *tmp, char *line)
{
	int		i;
	int		j;
	char	*tmp2;

	i = 0;
	j = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != ' ')
		j++;
	tmp2 = ft_strsub(line, i, j);
	if (ft_strcmp(tmp2, "sti") == 0)
		return (check_sti(tmp, line));
	else if (ft_strcmp(tmp2, "st") == 0)
		return (check_st(tmp, line));
	else if (ft_strcmp(tmp2, "live") == 0)
		return (check_live(tmp, line));
	else if (ft_strcmp(tmp2, "ld") == 0)
		return (check_ld(tmp, line));
	else if (ft_strcmp(tmp2, "fork") == 0)
		return (check_fork(tmp, line));
	else if (ft_strcmp(tmp2, "zjmp") == 0)
		return (check_zjmp(tmp, line));
	else if (ft_strcmp(tmp2, "add") == 0)
		return (check_add(tmp, line));
	else if (ft_strcmp(tmp2, "sub") == 0)
		return (check_sub(tmp, line));
}
