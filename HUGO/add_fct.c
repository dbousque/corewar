/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:05:35 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/18 13:39:57 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_c_name(t_function **file, char *line)
{
	int			i;
	int			j;
	char		*tmp2;
	t_function	*tmp;

	i = 0;
	j = 0;
	tmp2 = ft_strtrim(line);
	tmp2 = ft_strsub(tmp2, ft_strlen(NAME_CMD_STRING), ft_strlen(tmp2));
	tmp = new_function(tmp2);
	tmp->header = 1;
	ft_lstaddend_funct(file, tmp);
}

void	add_comment(t_function **file, char *line)
{
	int			i;
	int			j;
	char		*tmp2;
	t_function	*tmp;

	i = 0;
	j = 0;
	tmp2 = ft_strtrim(line);
	tmp2 = ft_strsub(tmp2, ft_strlen(COMMENT_CMD_STRING), ft_strlen(tmp2));
	tmp = new_function(tmp2);
	tmp->header = 1;
	ft_lstaddend_funct(file, tmp);
}

void	add_fun(t_function **file, char *line)
{
	int 		i;
	char		*tmp;
	t_function	*tmp2;

	i = 0;
	while (line[i] != LABEL_CHAR)
		i++;
	tmp = ft_strsub(line, 0, i);
}

void	add_sti(t_function **file, char *line)
{
}

void	add_st(t_function **file, char *line)
{
}

void	add_live(t_function **file, char *line)
{
}
