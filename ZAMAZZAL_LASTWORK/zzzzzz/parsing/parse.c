/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 04:18:38 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/20 20:38:24 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static void    free_node_notused(t_parse **lst)
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

static int is_operateur(t_parse **parse, t_parse **lst, t_utils *utils)
{
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

static int     add_argument(t_parse **lst, t_utils *utils)
{
    static t_parse *parse = NULL;
    size_t ret;

    if (!lst && utils && !parse->cmd)
        return (-1);
    else if (!lst && utils)
        return (1);
    else if (lst && !utils)
    {
        if (parse && !parse->cmd)
            free_node_notused(lst);
        parse = NULL;
        return (1);
    }
    if (!parse)
        parse = *lst;
    if ((ret = is_operateur(&parse, lst, utils)) != 0)
        return (ret);
    else
    {
        if ((if_redoraggr(&parse->lst_reder_aggr, utils)) == -1)
            return (-1);
        // check_argument(&utils->arg);
        argument_join(&parse->cmd, utils->arg);
    }
    return (1);
}

t_parse *parse_lst(char *cmd)
{
    t_utils *utils;
    t_parse *lst;
    size_t dernier_type = 0;

    if (!cmd || !cmd[0])
        return (NULL);
    if (!(utils = ( t_utils*)ft_memalloc(sizeof(t_utils))))
        return (NULL);
    if (!cmd || !(lst = (t_parse*)ft_memalloc(sizeof(t_parse))))
        return (NULL);
    utils->cmd = ft_strdup(cmd);
    while (1)
    {
        utils->index_arg += ft_skip_sep(&utils->cmd[utils->index_arg], " \t");
        while ((utils->arg = stock_next_argument(&utils->cmd[utils->index_arg], &utils->end_argument, &utils->cmd)))
        {
            utils->index_arg += utils->end_argument;
            utils->index_arg += ft_skip_sep(&utils->cmd[utils->index_arg], " \t");
            if (type_of_argument(utils->arg, 0))
                dernier_type = type_of_argument(utils->arg, 0);
            if ((add_argument(&lst, utils) == -1))
            {
                add_argument(&lst, NULL);
                return (exit_parsing(&lst, &utils, EXIT_FAILURE));
            }
            ft_strdel(&utils->arg);
        }
        if ((add_argument(NULL, utils) == -1) && !(dernier_type & (SEP | BG)))
            complet_type(&utils->cmd, dernier_type);
        else
        {
            add_argument(&lst, NULL);
            break ;
        }
    }
    return (exit_parsing(&lst, &utils, EXIT_SUCCESS));
}
