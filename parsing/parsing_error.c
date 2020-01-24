/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 02:13:58 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/21 22:00:13 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int     type_of_argument(const char *arg, size_t i)
{
    if ((!i || arg[i - 1] != '\\') && arg[i] == '|' && arg[i + 1] != '|')
        return (PIPE);
    else if (((!i || arg[i - 1] != '\\') && arg[i] == '&' && arg[i + 1] == '&')
    && (!i || ((arg[i - 1] != '<' && arg[i - 1] != '>'))
    || ((i - 1) && (arg[i - 2] == '&'))))
        return (AND);
    else if (((!i || arg[i - 1] != '\\') && arg[i] == '&')
    && (((!i || (arg[i - 1] != '<' && arg[i - 1] != '>'))
    && (arg[i + 1] != '<' && arg[i + 1] != '>')) || ((i - 1) && arg[i - 2] == '&')))
        return (BG);
    else if ((!i || arg[i - 1] != '\\') && arg[i] == '|' && arg[i + 1] == '|')
        return (OUR);
    else if ((!i || arg[i - 1] != '\\') && arg[i] == ';')
        return (SEP);
    return (0);
}

void free_lstreder(t_redirections **lst)
{
    if (!*lst)
        return ;
    if ((*lst)->next)
        free_lstreder(&(*lst)->next);
    ft_strdel(&(*lst)->file_name);
    ft_memdel((void**)lst);
}

void	free_lstpipe(t_parse **lst)
{
	if (!*lst)
		return ;
	if ((*lst)->pipe)
		free_lstpipe(&(*lst)->pipe);
    ft_strdel(&(*lst)->cmd);
    free_lstreder(&(*lst)->lst_reder_aggr);
    ft_memdel((void**)lst);
}

void	free_lstour(t_parse **lst);

void	free_lstand(t_parse **lst)
{
	if (!*lst)
		return ;
	free_lstpipe(&(*lst)->pipe);
	free_lstour(&(*lst)->if_fail);
	if ((*lst)->if_seccess)
		free_lstand(&(*lst)->if_seccess);
	ft_strdel(&(*lst)->cmd);
    free_lstreder(&(*lst)->lst_reder_aggr);
    ft_memdel((void**)lst);
}

void	free_lstour(t_parse **lst)
{
	if (!*lst)
		return ;
	free_lstpipe(&(*lst)->pipe);
	free_lstand(&(*lst)->if_seccess);
	if ((*lst)->if_fail)
		free_lstour(&(*lst)->if_fail);
    ft_strdel(&(*lst)->cmd);
    free_lstreder(&(*lst)->lst_reder_aggr);
    ft_memdel((void**)lst);
}

t_parse    *exit_parsing(t_parse **lst, t_utils **utils, t_ushort exit)
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

int     is_near(t_ushort type)
{
    ft_putstr_fd("42sh: parse error near ", 2);
    if (type == PIPE)
        ft_putendl_fd("`|'", 2);
    else if (type == AND)
        ft_putendl_fd("`&&'", 2);
    else if (type == OUR)
        ft_putendl_fd("`||'", 2);
    else if (type == SEP)
        ft_putendl_fd("`;;'", 2);
    else if (type == BG)
        ft_putendl_fd("`&'", 2);
    else if (type)
        ft_putendl_fd((char*)&type, 2);
    else
        ft_putendl_fd("`\\n'", 2);;
    return (-1);
}

int     redirec_isnear(t_ushort type)
{
    ft_putstr_fd("42sh: parse error near ", 2);
    if (type == APP_TO_FILE)
        ft_putendl_fd("`>>'", 2);
    else if (type == PRINT_TO_FILE)
        ft_putendl_fd("`>'", 2);
    else if (type == PRINT_NEXT_STRING)
        ft_putendl_fd("`<<<'", 2);
    else if (type == READ_FILE)
        ft_putendl_fd("`<'", 2);
    else if (type == HERE_DOCUMENT)
        ft_putendl_fd("`<<'", 2);
    else
        ft_putendl_fd("`\\n'", 2);;
    return (-1);
}
