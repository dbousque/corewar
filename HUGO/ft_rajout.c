/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rajout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:47:32 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/20 14:52:04 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		is_comment(char *str)
{
	int i;

	i = 0;
	while (COMMENT_CHARS[i])
	{
		if (str[0] == COMMENT_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}

char	*rem_com_if(char *str)
{
	int		i;
//	char	*tmp;

	i = 0;
//	tmp = NULL;
	while (str[i] != '#' && str[i])
		i++;
	if (str[i] == '\0')
		;
	else
		str = ft_strsub(str, 0, i);
	return (str);
}

int		is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] < '0' || str[i] > '9')
		i++;
	if (i > 1)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int		the_number(char *str)
{
	int		i;
	int		res;
	char	*tmp;

	i = 0;
	res = 0;
	while (str[i] < '0' && str[i] > '9')
		i++;
	tmp = ft_strsub(str, i, ft_strlen(str) - i);
	res = ft_atoi(tmp);
	return (res);
}
