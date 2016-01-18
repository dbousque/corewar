/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:05:35 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/18 14:08:11 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		g_nb_line;

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
	g_nb_line = 0;
	tmp = ft_strsub(line, 0, i);
	tmp2 = new_function(tmp);
	ft_lstaddend_funct(file, tmp2);
}

void	add_sti(t_function **file, char *line)
{
	t_function	*tmp;
	t_line		*tmp2;
	t_tempo		*vars;

	vars.j = 0;
	vars.i = 0;
	tmp = *file;
	g_nb_line++;
	vars.str2 = ft_strtrim(line);
	while (tmp)
		tmp = tmp->next;
	tmp2 = new_line(g_nb_line);
	ft_lstaddend_line(&tmp->lines, tmp2);
	while (vars.str2[i] != 'i')
		vars.i++;
	vars.j = vars.i;
	while (vars.str[vars.i] != SEPARATOR_CHAR)
		vars.i++;
	vars.param1 = ft_strsub(vars.str, vars.j, vars.i);
	vars.j = vars.i + 1;
	while (vars.str[vars.j] != SEPARATOR_CHAR)
		vars.j++;
	vars.param2 = ft_strsub(vars.str, vars.i, vars.j);
	vars.i = vars.j + 1;
	while (vars.str[vars.i] != '\n')
		vars.i++;
	vars.param3 = ft_strsub(vars.str, vars.j, vars.i);
}

void	add_st(t_function **file, char *line)
{
}

void	add_live(t_function **file, char *line)
{
}
