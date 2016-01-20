/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 16:36:03 by hbeaujou          #+#    #+#             */
/*   Updated: 2016/01/20 18:20:19 by hbeaujou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		g_tmp;
int		g_lines_tot;

int		is_label_char(char *str)
{
	char	*label;
	int		i;
	int		j;
	int		len;

	label = ft_strdup(LABEL_CHARS);
	len = ft_strlen(LABEL_CHARS);
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (label[j])
		{
			if (label[j] == str[i])
				break;
			j++;
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
	lenc = ft_strlen(COMMENT_CMD_STRING);
	tmp2 = ft_strsub(tmp, 0, lenn);
	if (ft_strcmp(tmp2, NAME_CMD_STRING) == 0)
	{
		tmp2 = ft_strsub(tmp, lenn, ft_strlen(tmp) - 1);
		tmp2 = ft_strtrim(tmp2);
		if (tmp2[0] == '"' && tmp2[ft_strlen(tmp2) - 1] == '"')
			return (100);
		else
			return (0);
	}
	tmp2 = ft_strsub(tmp, 0, lenc);
	if (ft_strcmp(tmp2, COMMENT_CMD_STRING) == 0)
	{
		tmp2 = ft_strsub(tmp, lenc, ft_strlen(tmp) - 1);
		tmp2 = ft_strtrim(tmp2);
		if (tmp2[0] == '"' && tmp2[ft_strlen(tmp2) - 1] == '"')
			return (101);
		else
			return (0);
	}
	return (0);
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
	else if (tmp[0] == '\0')
		return (103);
	else if (check_name_solo(tmp) == 1)
	{
		if (check_name_double(tmp) == 1)
			return (106);
		return (102);
	}
	else if (is_comment(tmp) == 1)
		return (105);
	else
		return (check_what_is(line));
}
void	add_command(int test, t_function **file, char *line)
{
	int			i;
	t_function	*tmp;
	char		*str3;

	i = 0;
	if (test == 100)
		add_c_name(file, line, test);
	else if (test == 101)
		add_comment(file, line, test);
	else if (test == 102)
		add_fun(file, line, test);
	else if (test == 106)
	{
		while (line[i] != LABEL_CHAR)
			i++;
		str3 = ft_strsub(line, 0, i);
		add_fun(file, str3, test);
		str3 = ft_strsub(line, i + 1, ft_strlen(line) - i);
		g_tmp = check_line(str3);
		add_command(g_tmp, file, str3);
	}
	else if (test == 103 || test == 105)
		;
	else if (test == 0)
		;
	else
	{
		if (last_fun_h(file) == 1)
		{
			tmp = new_function(NULL);
			ft_lstaddend_funct(file, tmp);
		}
		while (i < test)
			i++;
		i--;
		if (op_tab[i].nb_params == 1)
			add_line_1_param(file, line, test);
		else if (op_tab[i].nb_params == 2)
			add_line_2_param(file, line, test);
		else if (op_tab[i].nb_params == 3)
			add_line_3_param(file, line, test);
		else if (op_tab[i].nb_params == 4)
			add_line_4_param(file, line, test);
		else if (op_tab[i].nb_params == 5)
			add_line_5_param(file, line, test);
		else if (op_tab[i].nb_params == 6)
			add_line_6_param(file, line, test);
	}
}
