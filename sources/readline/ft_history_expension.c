/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_expension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:51:14 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 00:47:21 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_history_expansions4(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strnew(10000);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '!' && ft_isalpha(line[i + 1]))
		{
			if (expansion_word(i + 1, line) >= 0)
			{
				tmp = ft_join(tmp,
				g_readline->history[expansion_word(i + 1, line)], &j);
				i += add_to(line, i + 1);
			}
			else
				return (ft_ret(line, &tmp));
		}
		else
			tmp[j++] = line[i++];
	}
	ft_strdel(&line);
	return (tmp);
}

char	*ft_history_expansions3(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strnew(10000);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '!' && line[i + 1] == '-' && ft_isdigit(line[i + 2]))
		{
			if (g_readline->history[g_readline->indexfor_history -
			expansion_num(line, i + 2)])
				tmp = ft_join(tmp, g_readline->history[g_readline->
				indexfor_history - expansion_num(line, i + 2)], &j);
			i += 3;
		}
		else
			tmp[j++] = line[i++];
	}
	tmp[j] = '\0';
	ft_strdel(&line);
	return (tmp);
}

char	*ft_history_expansions2(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = ft_strnew(10000);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '!' && line[i + 1] == '!')
		{
			tmp = ft_join(tmp,
			g_readline->history[g_readline->indexfor_history - 1], &j);
			i += 2;
		}
		else
			tmp[j++] = line[i++];
	}
	tmp[j] = '\0';
	ft_strdel(&line);
	return (tmp);
}

char	*ft_history_expansions1(void)
{
	int		digit;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	digit = 0;
	tmp = (char *)ft_mmalloc(10000);
	while (g_readline->line[i] != '\0')
	{
		if (g_readline->line[i] == '!' &&
		ft_isdigit(g_readline->line[i + 1]))
		{
			if ((digit = expansion_num(g_readline->line,
			i + 1)) >= g_readline->indexfor_history)
				return (ft_join(tmp, &g_readline->line[i + 1], &j));
			tmp = ft_join(tmp, g_readline->history[digit], &j);
			i += 2;
		}
		else
			tmp[j++] = g_readline->line[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

void	ft_history_expansions(void)
{
	char	*tmp;
	int		len;

	if (!g_readline->history || g_readline->indexfor_history == 0)
		return ;
	len = g_readline->linelen +
	ft_strlen(g_readline->history[g_readline->indexfor_history - 1]);
	tmp = NULL;
	tmp = ft_history_expansions1();
	tmp = ft_history_expansions2(tmp);
	tmp = ft_history_expansions3(tmp);
	tmp = ft_history_expansions4(tmp);
	ft_strdel(&(g_readline->line));
	g_readline->line = ft_strdup(tmp);
	ft_strdel(&tmp);
}
