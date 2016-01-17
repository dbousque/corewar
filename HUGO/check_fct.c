/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 18:12:50 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/17 19:32:47 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		check_sti(char *tmp, char *line)
{
	int		i;
	int		j;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	j = 0;
	while (tmp[i] != 'i')
		i++;
	i++;
	if (tmp[i] != 'r')
		return (0);
	while (tmp[i] != SEPARATOR_CHAR) // A VERIFIER
		i++;
	j = i;
	while (tmp[j] != SEPARATOR_CHAR)
		j++;
	tmp2 = ft_strsub(tmp, i, j);
	i = j;
	while (tmp[j] != '\n') // A CHANGER POUR TOUT SUR LA MEME LIGNE
		j++;
	tmp3 = ft_strsub(tmp, i, j);
	// CHECK TMP2 ET TMP3 ET RETURN FINAL
}

int		check_st(char *tmp, char *line)
{
	int		i;
	int		j;
	char	*tmp2;

	i = 0;
	j = 0;
	while (tmp[i] != 't')
		i++;
	i++;
	if (tmp[i] != 'r')
		return (0);
	while (tmp[i] != SEPARATOR_CHAR) // A VERIFIER
		i++;
	j = i;
	while (tmp[j] != '\n')
		j++;
	tmp2 = ft_strsub(tmp, i, j);
	// CHECK TMP2 ET RETURN FINAL
}

int		check_live(char *tmp, char *line)
{
	int		i;
	int		j;
	char	*tmp2;

	i = 0;
	j = 0;
	while (tmp[i] != 'e')
		i++;
	i++;
	if (tmp[i] != DIRECT_CHAR)
		return (0);
	j = i;
	while (tmp[j] != '\n')
		j++;
	tmp2 = ft_strsub(tmp, i, j);
	// CHECK TMP2 ET RETURN FINAL
}

int		check_ld(char *tmp, char *line)
{
	int		i;
	int		j;
	char	*tmp2;

	i = 0;
	j = 0;
	while (tmp[i] != 'd')
		i++;
	i++;
}

int		check_fork(char *tmp, char *line)
{
}
