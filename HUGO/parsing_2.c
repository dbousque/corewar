/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 18:03:47 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/17 18:12:33 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		check_params(char *tmp)
{
	int		i;
	int		j;
	char	*tmp2;

	while (tmp[i] != SEPARATOR_CHAR)
		i++;
	tmp2 = ft_strsub(tmp2, 0, i);
	if (ft_strcmp(tmp2, "sti") == 0)
		return (check_sti(tmp));
	else if (ft_strcmp(tmp2, "st") == 0)
		return (check_st(tmp));
	else if (ft_strcmp(tmp2, "live") == 0)
		return (check_live(tmp));
	else if (ft_strcmp(tmp2, "ld") == 0)
		return (check_ld(tmp));
	else if (ft_strcmp(tmp2, "fork") == 0)
		return (check_fork(tmp));
	else if (ft_strcmp(tmp2, "zjmp") == 0)
		return (check_zjmp(tmp));
	else if (ft_strcmp(tmp2, "add") == 0)
		return (check_add(tmp));
	else if (ft_strcmp(tmp2, "sub") == 0)
		return (check_sub(tmp));
}
