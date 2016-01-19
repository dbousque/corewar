/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:26:46 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/19 17:32:51 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exit_prgm_nbr(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Indirect n'est pas un nombre\n", str, str2);
	exit(0);
}

void	exit_prgm_rg_big(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Registre trop grand\n", str, str2);
	exit(0);
}

void	exit_prgm_type_rg(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Un registre au mauvais endroit\n", str, str2);
	exit(0);
}

void	exit_prgm_type_ind(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Un indirect au mauvais endroit\n", str, str2);
	exit(0);
}

void	exit_prgm_type_dir_l(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Un direct label au mauvais endroit\n", str, str2);
	exit(0);
}

void	exit_prgm_type_dir_n(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Un direct number au mauvais endroit\n", str, str2);
	exit(0);
}

void	exit_prgm_lab_in(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Un direct label au mauvais endroit\n", str, str2);
	exit(0);
}

void	exit_prgm_fk_dir(char *str, char *str2)
{
	ft_printf("Fonction : %s | Commande : %s | Un direct number au mauvais endroit\n", str, str2);
	exit(0);
}
