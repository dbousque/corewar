/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:26:46 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/19 15:06:02 by hbeaujou         ###   ########.fr       */
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
	ft_putstr_fd("N'est pas un registre\n", 2);
	exit(0);
}

void	exit_prgm_type_ind(void)
{
	ft_putstr_fd("N'est pas un indirect\n", 2);
	exit(0);
}

void	exit_prgm_type_dir_l(void)
{
	ft_putstr_fd("N'est pas un direct label\n", 2);
	exit(0);
}

void	exit_prgm_type_dir_n(void)
{
	ft_putstr_fd("N'est pas un direct_number\n", 2);
	exit(0);
}

void	exit_prgm_lab_in(void)
{
	ft_putstr_fd("N'est pas un direct label valide\n", 2);
	exit(0);
}

void	exit_prgm_fk_dir(void)
{
	ft_putstr_fd("N'est pas un direct number valide\n", 2);
	exit(0);
}
