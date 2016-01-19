/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:26:46 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/19 16:39:04 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exit_prgm_nbr(void)
{
	ft_putstr_fd("Indirect n'est pas un nombre\n", 2);
	exit(0);
}

void	exit_prgm_rg_big(void)
{
	ft_putstr_fd("Registre trop grand\n", 2);
	exit(0);
}

void	exit_prgm_type_rg(void)
{
	ft_putstr_fd("Un registre au mauvais endroit\n", 2);
	exit(0);
}

void	exit_prgm_type_ind(void)
{
	ft_putstr_fd("Un indirect au mauvais endroit\n", 2);
	exit(0);
}

void	exit_prgm_type_dir_l(void)
{
	ft_putstr_fd("Un direct label au mauvais endroit\n", 2);
	exit(0);
}

void	exit_prgm_type_dir_n(void)
{
	ft_putstr_fd("Un direct number au mauvais endroit\n", 2);
	exit(0);
}

void	exit_prgm_lab_in(void)
{
	ft_putstr_fd("Un direct label au mauvais endroit\n", 2);
	exit(0);
}

void	exit_prgm_fk_dir(void)
{
	ft_putstr_fd("Un direct number au mauvais endroit\n", 2);
	exit(0);
}
