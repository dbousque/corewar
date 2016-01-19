/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 13:43:40 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/19 15:37:38 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_params(char *str, int val)
{
	char	*tmp;

	tmp = NULL;
	if (str[0] == 'r')
	{
		if (is_number(str) == 1 && the_number(str) <= REG_NUMBER)
		{
			if (val == T_REG)
				;
			else
				exit_prgm_type_rg();
		}
		else
			exit_prgm_rg_big();
	}
	else if (str[0] == DIRECT_CHAR)
	{
		if (str[1] == LABEL_CHAR)
		{
			if (is_label_char(ft_strsub(str, 2, ft_strlen(str) - 2)) == 1)
			{
				if (val == T_DIR)
					;
				else
					exit_prgm_type_dir_l();
			}
			else
				exit_prgm_lab_in();
		}
		else
		{
			if (is_number(str) == 1)
			{
				if (val == T_DIR)
					;
				else
					exit_prgm_type_dir_n();
			}
			else
				exit_prgm_fk_dir();
		}
	}
	else
	{
		if (is_number(str) == 1)
		{
			if (val == T_IND)
				;
			else
				exit_prgm_type_ind();
		}
		else
			exit_prgm_nbr();
	}
}

void	check_instruct(t_instruct **content)
{
	t_instruct	*tmp;
	char		*str;
	int			i;
	int			test;

	tmp = *content;
	i = 0;
	str = tmp->name;
	test = str_to_int(str);
	tmp = tmp->next;
	while (tmp)
	{
		check_params(tmp->name, op_tab[test].params_types[i]);
		i++;
	}
}

void	check_funct(t_line** lines)
{
	t_line	*tmp;

	tmp = *lines;
	while (tmp)
	{
		check_instruct(&tmp->content);
		tmp = tmp->next;
	}
}

void	check_file(t_function **file) // FAIRE PASSER LE NOM ET LA LIGNE POUR L AFFICHAGE DE L ERREUR
{
	t_function *tmp;

	tmp = *file;
	while (tmp)
	{
		if (tmp->header == 0)
			check_funct(&tmp->lines);
		tmp = tmp->next;
	}
}
