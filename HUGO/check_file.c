/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 13:43:40 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/20 18:45:30 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		is_in_tab(int a, int *tab, int i)
{
	if (tab[i] & a)
		return (1);
	return (0);
}

void	check_params(char *str, int *tab, int i, char *str2)
{
	char	*tmp;

	tmp = NULL;
	if (str[0] == 'r')
	{
		if (is_number(str) == 1 && the_number(str) <= REG_NUMBER)
		{
			if (is_in_tab(T_REG, tab, i))
				;
			else
				exit_prgm_type_rg(str2, str);
		}
		else
			exit_prgm_rg_big(str2, str);
	}
	else if (str[0] == DIRECT_CHAR)
	{
		if (str[1] == LABEL_CHAR)
		{
			if (is_label_char(ft_strsub(str, 2, ft_strlen(str) - 3)) == 1)
			{
				if (is_in_tab(T_DIR, tab, i))
					;
				else
					exit_prgm_type_dir_l(str2, str);
			}
			else
				exit_prgm_lab_in(str2, str);
		}
		else
		{
			if (str[1] == '-') // CAS DU NEGATIF A GERER MIEUX QUE CA
				;
			else if (is_number(str) == 1)
			{
				if (is_in_tab(T_DIR, tab, i)) // WTF NEGATIF PREND PAS DIR ON DIRAIT, ALORS QUE LD A BIEN UN DIR
					;
				else
					exit_prgm_type_dir_n(str2, str);
			}
			else
				exit_prgm_fk_dir(str2, str);
		}
	}
	else
	{
		if (is_number(str) == 1)
		{
			if (is_in_tab(T_IND, tab, i))
				;
			else
				exit_prgm_type_ind(str2, str);
		}
		else if (str[0] == LABEL_CHAR)
			;
		else
			exit_prgm_nbr(str2, str);
	}
}

void	check_instruct(t_instruct **content, char *str2)
{
	t_instruct	*tmp;
	char		*str;
	int			i;
	int			test;

	tmp = *content;
	i = 0;
	str = tmp->name;
	tmp = tmp->next;
	while (tmp)
	{
		test = str_to_int(str);
		check_params(tmp->name, op_tab[test].params_types, i, str2);
		tmp = tmp->next;
		i++;
	}
}

void	check_funct(t_line** lines, char *str2)
{
	t_line	*tmp;

	tmp = *lines;
	while (tmp)
	{
		check_instruct(&tmp->content, str2);
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
			check_funct(&tmp->lines, tmp->label);
		tmp = tmp->next;
	}
}
