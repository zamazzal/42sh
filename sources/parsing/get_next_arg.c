/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 20:45:14 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/12 04:56:40 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static	int		ft_getlinetype(int balance)
{
	if (balance & DQ)
		return (L_DQ);
	if (balance & SQ)
		return (L_SQ);
	return (L_B);
}

static	void	complet_cmd(char **line, int balance)
{
	char	*prompt;
	char	*complet;
	char	*tmp;

	if (balance & DQ)
		prompt = "dquote> \n";
	else if (balance & SQ)
		prompt = "quote> \n";
	else
		prompt = "> \n";
	g_line_type = ft_getlinetype(balance);
	complet = ft_readline(prompt);
	ft_putchar('\n');
	if (balance)
	{
		tmp = *line;
		*line = ft_jandf(tmp, "\n", 1, 0);
	}
	tmp = *line;
	*line = ft_jandf(tmp, complet, 1, 1);
}

static void		balance_manag(char *cmd, size_t ind, size_t *balance)
{
	if (cmd[ind] == '"' && (!ind || cmd[ind - 1] != '\\')
		&& !((*balance) & SQ))
		((*balance) & DQ) > 0 ? ((*balance) &= ~(DQ)) : ((*balance) |= DQ);
	if (cmd[ind] == '\'' && (!ind || cmd[ind - 1] != '\\')
		&& !((*balance) & DQ))
		((*balance) & SQ) > 0 ? ((*balance) &= ~(SQ)) : ((*balance) |= SQ);
	if ((cmd[ind] == '(' && (!ind || cmd[ind - 1] != '\\'))
		&& !((*balance) & (SQ | DQ)))
		(*balance) += IS_BRACKT;
	if ((cmd[ind] == ')' && (!ind || cmd[ind - 1] != '\\'))
		&& !((*balance) & (SQ | DQ)))
		(*balance) -= IS_BRACKT;
	if ((cmd[ind] == '{' && (!ind || cmd[ind - 1] != '\\'))
		&& !((*balance) & (SQ | DQ)))
		(*balance) += IS_CBRACKT;
	if ((cmd[ind] == '}' && (!ind || cmd[ind - 1] != '\\'))
		&& !((*balance) & (SQ | DQ)))
		(*balance) -= IS_CBRACKT;
}

static int		var_management(char **cmd, size_t *index,
	size_t balance, size_t begin_arg)
{
	if (((*cmd)[*index] == ' ' || (*cmd)[*index] < 0
		|| (*cmd)[*index] == '\n') && ((!(*index)
			|| ((*cmd)[*index - 1] != '\\')) && !balance))
		return (0);
	if (!balance && (type_of_argument(*cmd, *index) != 0))
	{
		if ((*index == begin_arg) && ((*index)++)
		&& ((*cmd)[(*index)] == (*cmd)[(*index) - 1]))
			(*index)++;
		return (0);
	}
	if ((!(*cmd)[++(*index)]) && (balance || (*cmd)[(*index) - 1] == '\\'))
		complet_cmd(cmd, balance);
	return (1);
}

char			*get_next_arg(char **cmd, size_t *index)
{
	char	*next_arg;
	size_t	begin_arg;
	size_t	balance;

	if (!*cmd || !(*cmd)[*index])
		return (NULL);
	(*index) += ft_skip_sep(&(*cmd)[*index], " \t\n");
	balance = 0;
	begin_arg = *index;
	g_ctrl_dsig = 1;
	while ((*cmd)[*index])
	{
		if (!g_ctrl_csig || !g_ctrl_dsig)
			return (NULL);
		balance_manag(*cmd, *index, &balance);
		if (!(var_management(cmd, index, balance, begin_arg)))
			break ;
	}
	next_arg = ft_strndup(&(*cmd)[begin_arg], (*index) - begin_arg);
	return (next_arg);
}
