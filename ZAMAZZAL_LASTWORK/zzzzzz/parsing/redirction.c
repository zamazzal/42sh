/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:50:04 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/20 20:45:16 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static size_t ret_red_type(char *arg, char type)
{
    if (ft_skip_sep(arg, &type) > 3)
        return (is_near(type));
    if (arg[0] == '<' && arg[1] == '<' && arg[2] == '<')
        return (PRINT_NEXT_STRING);
    if (arg[0] == '<' && arg[1] == '<')
        return (HERE_DOCUMENT);
    if (arg[0] == '<' && arg[1] == '>')
        return (READ_AND_WRITE_TO_FILE);
    if (arg[0] == '<')
        return (READ_FILE);
    if (arg[0] == '>' && arg[1] == '>')
        return (APP_TO_FILE);
    if (arg[0] == '>')
        return (PRINT_TO_FILE);
    if (arg[0] == '<')
        return (PRINT_TO_FILE);
    return (0);
}

static int ret_left_fd(t_utils *utils, size_t *start, int *red_type)
{
    char    *rest;

    if (*start == 0 && ((*red_type) & ALL_PRINT_TYPE))
         return (1);
    else if (*start == 0)
        return (0);
    (*start)--;
    if (utils->arg[*start] == '&' && !((*red_type) & ALL_READ_TYPE))
    {
        (*red_type) |= REDIRECT_STDIN_STDOUT;
        if (*start)
            (*start) -= 1;
    }
    if (!(*start) && ft_isdigit(utils->arg[*start]))
        return (ft_atoi(&utils->arg[*start]));
    else if (utils->arg[*start] != '&')
          (*start)++;
    return (0);
}

#include <readline/readline.h>
#include <readline/history.h>

static int ret_right_fd(t_utils *utils, size_t *end, int *red_type)
{
    *end += ft_skip_sep(&utils->arg[*end], "><");
    if (((*red_type) & ALL_READ_TYPE))
        return (0);
    if (utils->arg[*end] == '&' && !(*red_type & REDIRECT_STDIN_STDOUT)
    && ++(*end) && utils->arg[(*end)])
        (*red_type) |= SWAP_LFD_T_RFD;
    if (ft_isdigit(utils->arg[*end]) && ++(*end))
    {
        if (ft_atoi(&utils->arg[(*end) - 1]) > 9)
        {
            ft_putstr_fd("42sh: <", 2);
            ft_putnbr_fd(ft_atoi(&utils->arg[(*end) - 1]), 2);
            ft_putendl_fd("> bad file descriptor", 2);
            return (-1);
        }
        return (ft_atoi(&utils->arg[(*end) - 1]));
    }
    else if (utils->arg[*end] == '-' && !((*red_type) & REDIRECT_STDIN_STDOUT)
            && ((*red_type) & SWAP_LFD_T_RFD) && ++(*end))
        (*red_type) |= CLOSE_LFD;
    return (0);
}

static size_t  ret_file_name(char **file_name, t_utils *utils, size_t *end)
{
    size_t i;
    size_t type = 0;

    if (utils->arg[*end])
    {
        *file_name = ft_strdup(&utils->arg[*end]);
        *end = ft_strlen(utils->arg);
    }
    else
    {
        if (!(*file_name = stock_next_argument(&utils->cmd[utils->index_arg], &utils->end_argument, &utils->cmd)))
            return (is_near(0));
        if (type_of_argument(*file_name, 0))
            return (is_near(type_of_argument(*file_name, 0)));
        
        if ((((i = ft_strchr_index_shell(*file_name, '>')) != -1)
        || (i = ft_strchr_index_shell(*file_name, '<')) != -1)
        && ((type = ret_red_type(&(*file_name)[i], (*file_name)[i])) > 0) && type != -1)
            return (redirec_isnear(ret_red_type(&(*file_name)[i], (*file_name)[i])));
        else if (type == -1)
            return (-1);
        utils->index_arg += utils->end_argument;
        utils->index_arg += ft_skip_sep(&utils->cmd[utils->index_arg], " \t");
    }
    return (1);
}

void    read_herdoc(t_redirections **redirec_aggre)
{
    char *key;
    char *tmp;
    char *read;

    key = ft_strndup_shell((*redirec_aggre)->file_name, ft_strlen((*redirec_aggre)->file_name));
    ft_strdel(&(*redirec_aggre)->file_name);
    while ((read = readline("herdoc> ")))
    {
        if (!ft_strcmp(read, key))
            break ;
        tmp = read;
        read = ft_strjoin(read, "\n");
        free(tmp);
        tmp = (*redirec_aggre)->file_name;
        (*redirec_aggre)->file_name = ft_strjoin((*redirec_aggre)->file_name, read);
        free(tmp);
        ft_strdel(&read);
    }
    ft_strdel(&read);
}

size_t if_redoraggr(t_redirections **redirec_aggre, t_utils *utils)
{
    char            *rest;
    size_t          end;
    size_t          start;

    if (((end = ft_strchr_index_shell(utils->arg, '<')) != -1
    || (end = ft_strchr_index_shell(utils->arg, '>')) != -1)
    && ((!end || utils->arg[end - 1] != '\\')))
    {
        while (*redirec_aggre)
            redirec_aggre = &(*redirec_aggre)->next;
        start = end;
        if (!(*redirec_aggre = (t_redirections*)ft_memalloc(sizeof(t_redirections))))
            return (-1);
        if (((*redirec_aggre)->red_type = ret_red_type(&utils->arg[end], utils->arg[end])) == -1)
            return (-1);
        (*redirec_aggre)->left_fd = ret_left_fd(utils, &start, &(*redirec_aggre)->red_type);
        if (((*redirec_aggre)->right_fd = ret_right_fd(utils, &end, &(*redirec_aggre)->red_type)) == -1)
            return (-1);
        if (((*redirec_aggre)->right_fd == 0)
        && !((*redirec_aggre)->red_type & CLOSE_LFD) && !((*redirec_aggre)->red_type & SWAP_LFD_T_RFD))
            if (ret_file_name(&(*redirec_aggre)->file_name, utils, &end) == -1)
                return (-1);
        if ((*redirec_aggre)->red_type & HERE_DOCUMENT)
            read_herdoc(redirec_aggre);
        if (((*redirec_aggre)->red_type & PRINT_NEXT_STRING))
        {
            rest = (*redirec_aggre)->file_name;
            (*redirec_aggre)->file_name = ft_strjoin((*redirec_aggre)->file_name, "\n");
            free(rest);
        }
        rest = ft_strdup(&utils->arg[end]);
        ft_strclr(&utils->arg[start]);
        ft_strcat(utils->arg, rest);
    }
    return (0);
}
