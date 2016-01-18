/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:21:34 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/18 15:48:03 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		check_param(char *str)
{
	if (str[0] == 'r')
		return (REG);
	else if (str[0] == '%')
		return (DIRE);
	else
		return (INDIR);
}

void	make_line_1(t_function **file, t_tempo *vars, int test)
{
	t_function	*tmp;
	t_line		*tmp2;
	t_instruct	*tmp3;

	tmp = *file;
	while (tmp->next)
		tmp = tmp->next;
	tmp2 = new_line(g_nb_line);
	ft_lstaddend_line(&tmp->lines, tmp2);
	tmp3 = new_instruct(vars->name, LABEL, test);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param1, check_param(vars->param1), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
}

void	make_line_2(t_function **file, t_tempo *vars, int test)
{
	t_function	*tmp;
	t_line		*tmp2;
	t_instruct	*tmp3;

	tmp = *file;
	while (tmp->next)
		tmp = tmp->next;
	tmp2 = new_line(g_nb_line);
	ft_lstaddend_line(&tmp->lines, tmp2);
	tmp3 = new_instruct(vars->name, LABEL, test);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param1, check_param(vars->param1), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param2, check_param(vars->param2), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
}

void	make_line_3(t_function **file, t_tempo *vars, int test)
{
	t_function	*tmp;
	t_line		*tmp2;
	t_instruct	*tmp3;

	tmp = *file;
	while (tmp->next)
		tmp = tmp->next;
	tmp2 = new_line(g_nb_line);
	ft_lstaddend_line(&tmp->lines, tmp2);
	tmp3 = new_instruct(vars->name, LABEL, test);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param1, check_param(vars->param1), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param2, check_params(vars->param2), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param3, check_params(vars->param3), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
}

void	make_line_4(t_function **file, t_tempo *vars, int test)
{
	t_function	*tmp;
	t_line		*tmp2;
	t_instruct	*tmp3;

	tmp = *file;
	while (tmp->next)
		tmp = tmp->next;
	tmp2 = new_line(g_nb_line);
	ft_lstaddend_line(&tmp->lines, tmp2);
	tmp3 = new_instruct(vars->name, LABEL, test);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param1, check_param(vars->param1), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param2, check_params(vars->param2), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param3, check_params(vars->param3), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
	tmp3 = new_instruct(vars->param4, check_params(vars->param4), 0);
	ft_lstaddend_instruct(&tmp->lines->content, tmp3);
}
