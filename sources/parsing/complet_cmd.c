/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:48:58 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/16 03:36:20 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_getprompt_type(ushort type)
{
	if (type == PIPE)
		return (L_PIPE);
	if (type == AND)
		return (L_CMDAND);
	if (type == OUR)
		return (L_CMDOR);
	return (0);
}

void		complet_type(char **cmd, ushort dernier_type)
{
	char *prompt;
	char *complet;

	complet = NULL;
	if (dernier_type == PIPE)
		prompt = "pipe> \n";
	else if (dernier_type == AND)
		prompt = "cmdand> \n";
	else if (dernier_type == OUR)
		prompt = "cmdor> \n";
	else
		prompt = "> \n";
	g_line_type = ft_getprompt_type(dernier_type);
	complet = ft_readline(prompt);
	replace_alias(&complet);
	ft_putchar('\n');
	argument_join(cmd, complet);
	ft_strdel(&complet);
}

int			init_end_parse(char **cmd, t_parse **lst, t_utils **utils, int mode)
{
	if (mode == 1)
	{
		if (!*cmd || !(*cmd)[0])
			return (-1);
		if (!(*utils = (t_utils*)ft_memalloc(sizeof(t_utils))))
			return (-1);
		if (!(*lst = (t_parse*)ft_memalloc(sizeof(t_parse))))
			return (-1);
		(*utils)->cmd = ft_strdup(*cmd);
	}
	return (1);
}

int			parse_cmd(t_parse **lst, t_utils *utils)
{
	int last_type;

	last_type = 0;
	while ((utils->arg = get_next_arg(&utils->cmd, &utils->index_arg))
	&& (g_ctrl_dsig && g_ctrl_csig))
	{
		ret_tab_toline(utils->arg);
		if (type_of_argument(utils->arg, 0))
			last_type = type_of_argument(utils->arg, 0);
		if (utils->arg[0] && (add_argument(lst, utils) == -1))
			return (-1);
		ft_strdel(&utils->arg);
	}
	if (!g_ctrl_csig || !g_ctrl_dsig)
		return (-1);
	return (last_type);
}

int			validate_arg(char *arg, ushort type)
{
	int		index;
	int		error;

	if (!(type & (TRUNC_TF | READ_FILE)))
		return (1);
	error = 0;
	index = ft_strchr_index_shell(arg, '(');
	if (index > 0)
		error = 1;
	if (index == -1)
		return (1);
	index = ft_strchr_index_shell(arg, ')');
	if (index == -1)
		return (1);
	if (index < (int)ft_strlen(arg) - 1)
		error = 1;
	if (error)
	{
		ft_putendl_fd("42sh: syntax error near unexpected token '('", 2);
		return (-1);
	}
	return (1);
}
