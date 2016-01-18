/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fct_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:07:40 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/18 15:43:04 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_line_4_param(t_function **file, char *line, int test)
{
	t_tempo		*vars;

	vars->j = 0;
	vars->i = 0;
	g_nb_line++;
	vars->str2 = ft_strtrim(line);
	while (vars->str2[vars->i] != op_tab[test].name[ft_strlen(op_tab[test].name) - 1])
		vars->i++;
	vars->name = ft_strsub(vars->str2, 0, vars->i);
	vars->j = vars->i;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->param1 = ft_strsub(vars->str2, vars->j, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->param2 = ft_strsub(vars->str2, vars->i, vars->j);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->j++;
	vars->param3 = ft_strsub(vars->str2, vars->j, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != '\n')
		vars->j++;
	vars->param4 = ft_strsub(vars->str2, vars->i, vars->j);
	make_line_4(file, vars, test);
}

void	add_line_5_param(t_function **file, char *line, int test)
{
	t_tempo		*vars;

	vars->j = 0;
	vars->i = 0;
	g_nb_line++;
	vars->str2 = ft_strtrim(line);
	while (vars->str2[vars->i] != op_tab[test].name[ft_strlen(op_tab[test].name) - 1])
		vars->i++;
	vars->name = ft_strsub(vars->str2, 0, vars->i);
	vars->j = vars->i;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->param1 = ft_strsub(vars->str2, vars->j, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->param2 = ft_strsub(vars->str2, vars->i, vars->j);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->j++;
	vars->param3 = ft_strsub(vars->str2, vars->j, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->param4 = ft_strsub(vars->str2, vars->i, vars->j);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != '\n')
		vars->i++;
	vars->param5 = ft_strsub(vars->str2, vars->j, vars->i);
	make_line_5(file, vars, test);
}

void	add_line_6_param(t_function **file, char *line, int test)
{
	t_tempo		*vars;

	vars->j = 0;
	vars->i = 0;
	g_nb_line++;
	vars->str2 = ft_strtrim(line);
	while (vars->str2[vars->i] != op_tab[test].name[ft_strlen(op_tab[test].name) - 1])
		vars->i++;
	vars->name = ft_strsub(vars->str2, 0, vars->i);
	vars->j = vars->i;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->param1 = ft_strsub(vars->str2, vars->j, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->param2 = ft_strsub(vars->str2, vars->i, vars->j);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->j++;
	vars->param3 = ft_strsub(vars->str2, vars->j, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->param4 = ft_strsub(vars->str2, vars->i, vars->j);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->param5 = ft_strsub(vars->str2, vars->j, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != '\n')
		vars->i++;
	vars->param6 = ft_strsub(vars->str2, vars->i, vars->j);
	make_line_6(file, vars, test);
}
