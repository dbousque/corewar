/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:35:09 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/18 13:46:43 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_lstaddend_funct(t_function **alst, t_function *new_r)
{
	t_function	*tmp;

	tmp = *alst;
	if (!tmp)
		*alst = new_r;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_r;
	}
}

void		ft_lstaddend_line(t_line **alst, t_line *new_r)
{
	t_line	*tmp;

	tmp = *alst;
	if (!tmp)
		*alst = new_r;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_r;
	}
}

void		ft_lstaddend_instruct(t_instruct **alst, t_instruct *new_r)
{
	t_instruct	*tmp;

	tmp = *alst;
	if (!tmp)
		*alst = new_r;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_r;
	}
}

t_function	*new_function(char *str)
{
	t_function *res;

	if (!(res = (t_function *)malloc(sizeof(t_function))))
		return (NULL);
	res->header = 0;
	res->bytes_written = 0;
	res->label = ft_strdup(str);
	res->lines = NULL;
	res->next = NULL;
	return (res);
}

t_line		*new_line(int count)
{
	t_line *res;

	if (!(res = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	res->numero = count;
	res->content = NULL;
	res->next = NULL;
	return (res);
}

t_instruct	*new_instruct(char *str, int typ, int opcod)
{
	t_instruct *res;

	if (!(res = (t_instruct *)malloc(sizeof(t_instruct))))
		return (NULL);
	res->name = ft_strdup(str);
	res->type = typ;
	res->opcod = opcode;
	res->next = NULL;
	return (res);
}
