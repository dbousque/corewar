/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fct_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:07:40 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/20 15:10:37 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_line_4_param(t_function **file, char *line, int test)
{
	t_tempo		*vars;

	vars = (t_tempo *)malloc(sizeof(t_tempo));
	vars->j = 0;
	vars->i = 0;
	g_nb_line++;
	vars->str2 = ft_strtrim(line);
	vars->str2 = deblank(vars->str2);
	vars->str2 = rem_com_if(vars->str2);
	while (vars->str2[vars->i] != op_tab[test - 1].name[ft_strlen(op_tab[test - 1].name) - 1])
		vars->i++;
	vars->i++;
	vars->name = ft_strsub(vars->str2, 0, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->param1 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->i++;
	vars->param2 = ft_strsub(vars->str2, vars->i, vars->j - vars->i);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->j++;
	vars->param3 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != '\0')
		vars->j++;
	vars->i++;
	vars->param4 = ft_strsub(vars->str2, vars->i, vars->j);
	make_line_4(file, vars);
	free(vars);
}

void	add_line_5_param(t_function **file, char *line, int test)
{
	t_tempo		*vars;

	vars = (t_tempo *)malloc(sizeof(t_tempo));
	vars->j = 0;
	vars->i = 0;
	g_nb_line++;
	vars->str2 = ft_strtrim(line);
	vars->str2 = deblank(vars->str2);
	vars->str2 = rem_com_if(vars->str2);
	while (vars->str2[vars->i] != op_tab[test - 1].name[ft_strlen(op_tab[test - 1].name) - 1])
		vars->i++;
	vars->i++;
	vars->name = ft_strsub(vars->str2, 0, vars->i);
	vars->j = vars->i + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->param1 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->i++;
	vars->param2 = ft_strsub(vars->str2, vars->i, vars->j - vars->i);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->j++;
	vars->param3 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->i++;
	vars->param4 = ft_strsub(vars->str2, vars->i, vars->j - vars->i);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != '\0')
		vars->i++;
	vars->j++;
	vars->param5 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	make_line_5(file, vars);
	free(vars);
}

void	add_line_6_param(t_function **file, char *line, int test)
{
	t_tempo		*vars;

	vars = (t_tempo *)malloc(sizeof(t_tempo));
	vars->j = 0;
	vars->i = 0;
	g_nb_line++;
	vars->str2 = ft_strtrim(line);
	vars->str2 = deblank(vars->str2);
	vars->str2 = rem_com_if(vars->str2);
	while (vars->str2[vars->i] != op_tab[test - 1].name[ft_strlen(op_tab[test - 1].name) - 1])
		vars->i++;
	vars->i++;
	vars->name = ft_strsub(vars->str2, 0, vars->i);
	vars->j = vars->i;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->param1 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->i++;
	vars->param2 = ft_strsub(vars->str2, vars->i, vars->j - vars->i);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->j++;
	vars->param3 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != SEPARATOR_CHAR)
		vars->j++;
	vars->i++;
	vars->param4 = ft_strsub(vars->str2, vars->i, vars->j - vars->i);
	vars->i = vars->j + 1;
	while (vars->str2[vars->i] != SEPARATOR_CHAR)
		vars->i++;
	vars->j++;
	vars->param5 = ft_strsub(vars->str2, vars->j, vars->i - vars->j);
	vars->j = vars->i + 1;
	while (vars->str2[vars->j] != '\0')
		vars->i++;
	vars->i++;
	vars->param6 = ft_strsub(vars->str2, vars->i, vars->j - vars->i);
	make_line_6(file, vars);
	free(vars);
}
