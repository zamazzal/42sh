/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 04:18:38 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/12 03:57:03 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		free_node_notused(t_parse **lst)
{
	if (!*lst)
		return ;
	if ((*lst)->next && (*lst)->next->cmd)
		free_node_notused(&(*lst)->next);
	else if ((*lst)->next)
		ft_memdel((void**)&(*lst)->next);
	else if ((*lst) && !(*lst)->cmd)
		ft_memdel((void**)&(*lst));
}

int				is_operateur(t_parse **parse, t_parse **lst, t_utils *utils)
{
	if ((*parse)->cmd && type_of_argument(utils->arg, 0) != 0)
		if ((*parse)->cmd[0])
			setervars(&(*parse)->cmd);
	if (!ft_strcmp(utils->arg, "|"))
		return (change_to_pipe(parse));
	else if (!ft_strcmp(utils->arg, "&&"))
		return (change_to_opand(parse, *lst));
	else if (!ft_strcmp(utils->arg, "||"))
		return (change_to_opor(parse, *lst));
	else if (!ft_strcmp(utils->arg, ";;"))
	{
		is_near(SEP);
		return (-1);
	}
	else if (!ft_strcmp(utils->arg, ";"))
	{
		if ((*parse)->cmd)
			return (change_to_seperat(parse, *lst));
		return (1);
	}
	else if (!ft_strcmp(utils->arg, "&"))
		return (is_background(parse, *lst));
	return (0);
}

static size_t	complet_check_parse(t_parse **parse, t_parse **lst, int mode)
{
	if (mode == 1)
	{
		if (!(*parse) || !(*parse)->cmd)
			return (-1);
		if ((*parse)->cmd && (*parse)->cmd[0])
			setervars(&(*parse)->cmd);
		if ((*parse)->cmd && !(*parse)->cmd[0] && !(*parse)->lst_reder_aggr)
			argument_join(&(*parse)->cmd, "true");
		return (1);
	}
	if (mode == 2)
	{
		if ((*parse) && !(*parse)->cmd)
			free_node_notused(lst);
		*parse = NULL;
		return (1);
	}
	if (mode == 3)
		(*parse) = *lst;
	return (1);
}

int				add_argument(t_parse **lst, t_utils *utils)
{
	static t_parse	*parse = NULL;
	size_t			ret;

	if (!parse && *lst && utils)
		complet_check_parse(&parse, lst, 3);
	if (!lst && utils)
		return (complet_check_parse(&parse, NULL, 1));
	if (!utils && lst)
		return (complet_check_parse(&parse, lst, 2));
	if ((ret = is_operateur(&parse, lst, utils)) != 0)
		return (ret);
	else
	{
		if (!parse->cmd)
			save_last_herdoc(NULL, 0);
		if ((cut_if_redoraggr(&parse->lst_reder_aggr, utils)) == -1)
			return (-1);
		argument_join(&parse->cmd, utils->arg);
	}
	return (1);
}

t_parse			*parse_lst(char **cmd)
{
	t_utils	*utils;
	t_parse	*lst;
	int		exit_type;
	size_t	last_type;

	last_type = 0;
	exit_type = 0;
	if (init_end_parse(cmd, &lst, &utils, 1) == -1)
		return (NULL);
	while (1)
	{
		if ((last_type = parse_cmd(&lst, utils)) == -1)
		{
			exit_type = 1;
			break ;
		}
		if ((add_argument(NULL, utils) == -1) && !(last_type & (SEP | BG)))
			complet_type(&utils->cmd, last_type);
		else
			break ;
	}
	ft_strdel(cmd);
	*cmd = ft_strdup(utils->cmd);
	add_argument(&lst, NULL);
	return (exit_parsing(&lst, &utils, exit_type));
}
