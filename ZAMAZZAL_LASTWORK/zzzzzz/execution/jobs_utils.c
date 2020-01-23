/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 00:12:55 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/22 18:09:13 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int     if_signaled(int status)
{
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGSEGV)
            ft_putendl_fd(" segmentation violation", 2);
        else if (WTERMSIG(status) == SIGABRT)
            ft_putendl_fd(" abort program", 2);
        else if (WTERMSIG(status) == SIGBUS)
            ft_putendl_fd(" bus error", 2);
        else if (WTERMSIG(status) == SIGKILL)
            ft_putendl_fd(" program killed", 2);
        else if (WTERMSIG(status) == SIGQUIT)
            ft_putendl_fd(" quit progam", 2);
        else if (WTERMSIG(status) == SIGILL)
            ft_putendl_fd(" illegal instruction", 2);
        else if (WTERMSIG(status) == SIGTRAP)
            ft_putendl_fd(" trace trap", 2);
        else if (WTERMSIG(status) == SIGTERM)
            ft_putendl_fd(" process terminated.", 2);
        else
        {
            ft_putstr_fd(" process termine a cause d'un signal nbr:", 2);
            ft_putnbr_fd((int)WTERMSIG(status), 2);
            ft_putendl_fd(".", 2);
        }
    }
    else
        return (0);
    return (1);
}

void    print_command(t_parse *lst)
{
    if (!lst)
        return ;
    ft_putstr(lst->cmd);
    if (lst->pipe)
    {
        ft_putstr(" | ");
        print_command(lst->pipe);
    }
    if (lst->if_seccess)
    {
        ft_putstr(" && ");
        print_command(lst->if_seccess);
    }
    if (lst->if_fail)
    {
        ft_putstr(" || ");
        print_command(lst->if_fail);
    }
}

void    delete_node(t_jobs *node)
{
    t_jobs **lst;
    t_jobs *previous;

    lst = &(*save_objet())->lst_jobs;
    if (!*lst)
        return ;
    previous = NULL;
    while ((*lst)->pgid != node->pgid)
    {
        previous = *lst;
        lst = &(*lst)->next;
    }
    if ((*lst)->pgid == node->pgid)
    {
        if (previous)
            previous->next = node->next;
        else
            *lst = (*lst)->next;
        exit_parsing(&node->node_cmd, NULL, 1);
        free(node);
    }
}

// void    if_bgp_exited(t_objet *objet, t_jobs *jobs, int status)
// {
//     t_parse *tmp;

//     tmp = NULL;
//     ft_putchar('\n');
//     ft_putchar('[');
//     ft_putnbr(jobs->proc_id);
//     ft_putchar(']');
//     (jobs->mode & IS_SELECTED) ? ft_putstr("+ ") : ft_putstr("- ");
//     ft_putnbr(jobs->pgid);
//     ft_putchar('\t');
//     print_command(jobs->node_cmd);
//     ft_putchar('\t');
//     if (!if_signaled(status))
//         ft_putendl("Done");
//     if ((WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0))
//         && jobs->node_cmd->if_fail)
//             tmp = jobs->node_cmd->if_fail;
//     else if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && jobs->node_cmd->if_seccess)
//             tmp = jobs->node_cmd->if_seccess;
// }

void    check_lstjobs(t_objet *objet)
{
    t_jobs *jobs;
    t_parse *ptr;
    t_parse *tmp;
    int status;

    if (objet->lst_jobs)
    {
        jobs = objet->lst_jobs;
        while (jobs)
        {
            if (waitpid(jobs->pgid, &status, WNOHANG | WUNTRACED) != 0)
            {
                if (!WIFSTOPPED(status))
                {
                    tmp = NULL;
                    ft_putchar('\n');
                    ft_putchar('[');
                    ft_putnbr(jobs->proc_id);
                    ft_putchar(']');
                    (jobs->mode & IS_SELECTED) ? ft_putstr("+ ") : ft_putstr("- ");
                    ft_putnbr(jobs->pgid);
                    ft_putstr("\t");
                    print_command(jobs->node_cmd);
                    ft_putchar(' ');
                    if (!(if_signaled(status)))
                        ft_putendl(" done");
                    if ((WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0))
                        && jobs->node_cmd->if_fail)
                            tmp = jobs->node_cmd->if_fail;
                    else if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && jobs->node_cmd->if_seccess)
                        tmp = jobs->node_cmd->if_seccess;
                    if (tmp)
                    {
                        if (jobs->node_cmd->if_fail)
                            jobs->node_cmd->if_fail = NULL;
                        else
                            jobs->node_cmd->if_seccess = NULL;
                        tmp->bg = 1;
                        ptr = objet->lst_parse;
                        if (ptr)//exec some command .. 
                        {
                            while (ptr->next)
                                ptr = ptr->next;
                            ptr->next = tmp;
                        }
                        else//read command ...
                        {
                            objet->lst_parse = tmp;
                            exec_lstparse(objet);
                        }
                    }
                    delete_node(jobs);
                }
                else
                {
                    ft_putnbr(jobs->pgid);
                    ft_putstr(" Stopped");
                    if (WSTOPSIG(status) == SIGTTIN)
                        ft_putstr(" (tty input)");
                    if (WSTOPSIG(status) == SIGTTOU)
                        ft_putstr(" (tty output");
                    ft_putchar('\n');
                    jobs->mode &= ~(IS_BACKGROUND);
                    jobs->mode |= (IS_SUSPEND);
                }
            }
            jobs = jobs->next;
        }
    }
}
