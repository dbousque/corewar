/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 18:03:47 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/18 16:19:39 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		check_params(char *line)
{
	int		i;
	int		j;
	int		k;
	char	*tmp2;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != ' ')
		j++;
	tmp2 = ft_strsub(line, i, j);
	while (ft_strcmp(tmp2, op_tab[k].name) != 0 && op_tab[k].nb_params != 0)
		k++;
	return (k);
}

int		check_name_solo(char *str)
{
	int	i;
	int	j;
	int fini;

	i = 0;
	fini = 0;
	while (str[i] && fini == 0)
	{
		j = 0;
		while (LABEL_CHARS[j])
		{
			if (str[i] == LABEL_CHARS[j])
				break ;
			j++;
		}
		if (LABEL_CHARS[j] == '\0')
			fini = 1;
		else
			i++;
	}
	if (str[i] == LABEL_CHAR)
		return (1);
	return (0);
}
