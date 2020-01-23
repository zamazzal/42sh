/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:34:51 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/21 22:16:35 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"


static void   create_npath(char *cmd, char **cmd_path, char **path)
{
    char *tmp;

    ft_strdel(cmd_path);
    *cmd_path = ft_strjoin(*path, "/"); 
    ft_strdel(path);
    tmp = *cmd_path;
    *cmd_path = ft_strjoin(*cmd_path, cmd);
    free(tmp);
}

char    *get_path_cmd(char *cmd, char **environ)
{
    char *cmd_path;
    char **paths;
    char *val;
    size_t i;

    i = 0;
    if (!(val = ft_getenv("PATH")))
        return (NULL);
    printf("zamazzal\n");
    if (!(paths = ft_strsplit(ft_strchr(val, '=') + 1, ':')))
        return (NULL);
    free(val);
    cmd_path = ft_strdup(cmd);
    while (access(cmd_path, F_OK | X_OK) != 0)
    {
        if (!(access(cmd_path, F_OK)))
        {
            ft_putstr_fd("42sh: ", 2);
            ft_putstr_fd("parmission denied: ", 2);
            ft_putendl_fd(cmd_path, 2);
        }
        if (!paths[i])
            break ;
        create_npath(cmd, &cmd_path, &paths[i++]);
    }
    if (!paths[i])
    {
        ft_putstr_fd("42sh: ", 2);
        ft_putstr_fd("command not found: ", 2);
        ft_putendl_fd(cmd, 2);
        ft_strdel(&cmd_path);
    }
    else
        free_double(&paths[i]);
    free(paths);
    return (cmd_path);
}