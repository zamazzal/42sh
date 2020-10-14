/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 03:47:32 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 17:12:13 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	free_lstreder(t_redirections **lst)
{
	if (!*lst)
		return ;
	if ((*lst)->next)
		free_lstreder(&(*lst)->next);
	ft_strdel(&(*lst)->file_name);
	ft_memdel((void**)lst);
}

static void	free_lstpipe(t_parse **lst)
{
	if (!*lst)
		return ;
	if ((*lst)->pipe)
		free_lstpipe(&(*lst)->pipe);
	ft_strdel(&(*lst)->cmd);
	ft_strdel(&(*lst)->path);
	free_lstreder(&(*lst)->lst_reder_aggr);
	ft_memdel((void**)lst);
}

static void	free_lstand(t_parse **lst)
{
	if (!*lst)
		return ;
	free_lstpipe(&(*lst)->pipe);
	free_lstour(&(*lst)->if_fail);
	if ((*lst)->if_seccess)
		free_lstand(&(*lst)->if_seccess);
	ft_strdel(&(*lst)->cmd);
	ft_strdel(&(*lst)->path);
	free_lstreder(&(*lst)->lst_reder_aggr);
	ft_memdel((void**)lst);
}

void		free_lstour(t_parse **lst)
{
	if (!*lst)
		return ;
	free_lstpipe(&(*lst)->pipe);
	free_lstand(&(*lst)->if_seccess);
	if ((*lst)->if_fail)
		free_lstour(&(*lst)->if_fail);
	ft_strdel(&(*lst)->cmd);
	ft_strdel(&(*lst)->path);
	free_lstreder(&(*lst)->lst_reder_aggr);
	ft_memdel((void**)lst);
}

t_parse		*exit_parsing(t_parse **lst, t_utils **utils, ushort exit)
{
	t_parse *tmp;

	if (exit == EXIT_FAILURE)
		while (*lst)
		{
			tmp = (*lst)->next;
			free_lstand(&(*lst)->if_seccess);
			free_lstour(&(*lst)->if_fail);
			free_lstpipe(lst);
			*lst = tmp;
		}
	if (utils && (*utils))
	{
		ft_strdel(&(*utils)->cmd);
		ft_strdel(&(*utils)->arg);
		ft_memdel((void**)utils);
	}
	return (*lst);
}
