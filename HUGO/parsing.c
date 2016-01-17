/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 16:36:03 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/17 19:08:30 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_label_char(char *str)
{
	char	*label;
	int		i;
	int		j;
	int		len;

	label = ft_strdup(LABEL_CHARS);
	len = ft_strlen(LABEL_CHARS)
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (label[j])
		{
			if (label[j] == str[i])
				break;
		}
		if (j == len - 1)
			return (0);
		i++;
	}
	return (1);
}

int		check_begin(char *tmp)
{
	char	*tmp2;
	int		lenn;
	int		lenc;

	lenn = ft_strlen(NAME_CMD_STRING);
	lenn = ft_strlen(COMMENT_CMD_STRING);
	tmp2 = ft_strsub(tmp, 0, lenn);
	if (ft_strcmp(tmp2, NAME_CMD_STRING) == 0)
	{
		tmp2 = ft_strsub(tmp, lenn, ft_strlen(tmp) - 1);
		if (tmp2[0] == '"' && tmp2[ft_strlen(tmp) - 1] == '"')
			return (1);
		else
			return (0);
	}
	tmp2 = ft_strsub(tmp, 0, lenc);
	if (ft_strcmp(tmp2, COMMENT_CMD_STRING) == 0)
	{
		tmp2 = ft_strsub(tmp, lenc, ft_strlen(tmp) - 1);
		if (tmp2[0] == '"' && tmp2[ft_strlen(tmp) - 1] == '"')
			return (2);
		else
			return (0);
	}
	return (0);
}

int		check_function(char *tmp, char *line)
{
	int		i;
	int		j;
	int		len;
	t_tempo	vars;

	i = 0;
	j = 0;
	len = ft_strlen(tmp);
	while (tmp[i] != LABEL_CHAR)
		i++;
	vars->tmp2 = ft_strsub(tmp, 0, i);
	if (is_label_char(vars->tmp2) == 0)
		return (0);
	vars->name = ft_strdup(vars->tmp2);
	vars->tmp2 = ft_strsub(tmp, i, len);
	return (check_params(vars->tmp2, line));
}

int		check_line(char *line)
{
	char		*tmp;
	char		*test1;
	char		*test2;
	static int	begin = 0;

	test1 = ft_strdup(NAME_CMD_STRING);
	test2 = ft_strdup(COMMENT_CMD_STRING);
	tmp = ft_strtrim(line);
	if (tmp[0] == test1[0] || tmp[0] == test2[0])
	{
		if (begin > 1)
			return (0);
		begin++;
		return (check_begin(tmp));
	}
	else
		return (check_function(tmp, line));
}

void	add_command(int test, t_function **file)
{
}
