/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:36:09 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 17:07:24 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*ft_strndup_shell(char *cmd, size_t n)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	balance;

	j = 0;
	i = 0;
	balance = 0;
	if (!(str = ft_strnew(ft_strlen(cmd))))
		return (NULL);
	while (cmd[i] && i < n)
	{
		if (cmd[i] == '"' && (!i || cmd[i - 1] != '\\') && !(balance & 2))
			balance = (balance > 0) ? 0 : 1;
		else if (cmd[i] == '\'' && (!i || cmd[i - 1] != '\\') && !(balance & 1))
			balance = (balance > 0) ? 0 : 2;
		if (cmd[i] == '\\' && (!i || cmd[i - 1] != '\\'))
			i++;
		if ((!i || cmd[i - 1] != '\\') &&
		((cmd[i] == '"' && !(balance & 2))
		|| (cmd[i] == '\'' && !(balance & 1))))
			i += (cmd[i] == cmd[i + 1]) ? 2 : 1;
		str[j++] = cmd[i++];
	}
	return (str);
}

int			ft_strchr_index_shell(char *cmd, char c)
{
	size_t i;
	size_t balance;

	balance = 0;
	i = 0;
	if (!cmd)
		return (-1);
	while (cmd[i])
	{
		if (cmd[i] == '"' && (!i || cmd[i - 1] != '\\') && !(balance & 2))
			balance = (balance > 0) ? 0 : 1;
		else if (cmd[i] == '\'' && (!i || cmd[i - 1] != '\\') && !(balance & 1))
			balance = (balance > 0) ? 0 : 2;
		else if (cmd[i] == c && (!i || cmd[i - 1] != '\\') && !balance)
			break ;
		i++;
	}
	if (cmd[i] == c)
		return (i);
	return (-1);
}

void		argument_join(char **cmd, char *argument)
{
	char *tmp;

	if (!cmd)
		return ;
	if (!*cmd)
		*cmd = ft_strdup(argument);
	else
	{
		tmp = *cmd;
		*cmd = ft_strjoin(tmp, " ");
		ft_strdel(&tmp);
		tmp = *cmd;
		*cmd = ft_strjoin(*cmd, argument);
		ft_strdel(&tmp);
		tmp = *cmd;
		*cmd = ft_strtrim(tmp);
		ft_strdel(&tmp);
	}
}

int			change_to_pipe(t_parse **parse)
{
	if (!(*parse)->cmd)
	{
		is_near(PIPE);
		return (-1);
	}
	if (!((*parse)->pipe = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (-1);
	*parse = (*parse)->pipe;
	return (1);
}

int			point_final_node(t_parse **parse)
{
	if (!*parse)
		return (0);
	if ((*parse)->next && (*parse = (*parse)->next))
		return (point_final_node(parse));
	if ((*parse)->if_fail || (*parse)->if_seccess)
	{
		if ((*parse)->if_fail)
			*parse = (*parse)->if_fail;
		else
			*parse = (*parse)->if_seccess;
		point_final_node(parse);
		return (1);
	}
	return (1);
}
