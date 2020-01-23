/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:04:05 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/21 19:55:10 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

//jobs [nbr] ...
//      -l : list all avaible jobs (par defaut)
//      -r : list all jobs runing in the background
//      -s : list all jobs stopped.
//      -p : list all jobs pid.
static int     get_type(int type)
{
    int typ2;

    if (!type)
        return (0);
    typ2 = 1;
    while (--type)
        typ2 *= 2;
    return (typ2);
}

static void     jobs_usage(char c)
{
    ft_putstr_fd("jobs: ", 2);
    ft_putchar_fd(c, 2);
    ft_putendl_fd(" invalide option.", 2);
    ft_putendl_fd("\tusage: jobs ... || jobs -[lbsp]", 2);
    ft_putendl_fd("\t\t-l: list jobs (par defaut).", 2);
    ft_putendl_fd("\t\t-r: list jobs runing in the background.", 2);
    ft_putendl_fd("\t\t-s: list stopped jobs.", 2);
    ft_putendl_fd("\t\t-p: list jobs pid.", 2);
}
// #define FLAGS_L 2048
// #define FLAGS_R 131072
// #define FLAGS_S 262144
// #define FLAGS_P 32768
int get_option(char **argv, int *option)
{
    size_t i;
    size_t j;

    i = 0;
    while (argv[++i] && argv[i][0] == '-')
    {
        j = 1;
        while (argv[i][j])
        {
            if (argv[i][j] == 'l' || argv[i][j] == 'r' || argv[i][j] == 's' || argv[i][j] == 'p')
            {
                if (argv[i][j] == 'p' || argv[i][j] == 'l')
                    (*option) &= ~(FLAGS_P | FLAGS_L);
                if (argv[i][j] == 's' || argv[i][j] == 'r')
                    (*option) &= ~(FLAGS_R | FLAGS_S);
                (*option) |= get_type(argv[i][j] - 96);
            }
            else if (argv[i][j] != '-')
            {
                jobs_usage(argv[i][j]);
                return (-1);
            }
            else if (argv[i][j] == '-' && argv[i][j + 1] == '\0')
                return (i + 1);
            else if (argv[i][j] == '-')
            {
                jobs_usage(argv[i][j + 1]);
                return (-1);
            }
            j++;
        }
    }
    return (i);
}

void    print_node(t_jobs *node, int option)
{
    if ((option & FLAGS_S) && !(node->mode & IS_SUSPEND))
        return ;
    if ((option & FLAGS_R) && !(node->mode & IS_BACKGROUND))
        return ;
    if (!(option & FLAGS_P))
        ft_putchar('[');
    if (!(option & FLAGS_P))
        ft_putnbr(node->proc_id);
    if (!(option & FLAGS_P))
        ft_putstr("] ");
    if (option & FLAGS_P)
        ft_putnbr(node->pgid);
    ft_putchar(' ');
    if (!(option & FLAGS_P))
        (node->mode & IS_SELECTED) > 0 ? ft_putstr("+ ") : ft_putstr("- ");
    if (!(option & FLAGS_P))
        (node->mode & IS_SUSPEND) > 0 ? ft_putstr("suspend\t") : ft_putstr("running\t");
    if (!(option & FLAGS_P))
        print_command(node->node_cmd);
    ft_putchar('\n');
}

int     jobs_builtin(char **argv, t_objet *objet)
{
    t_jobs      *jobs;
    size_t      i;
    int         option = 0;
    int         flags = 0;

    if ((i = get_option(argv, &option)) == -1)
        return (1);//exit failure
    if (!objet->lst_jobs)
        return (0);//exit Seccuss
    if (!argv[i])
        flags = 1;
    jobs = objet->lst_jobs;
    while (jobs)
    {
        if (flags || (ft_atoi(argv[i]) == jobs->proc_id))
        {
            if (!flags)
                i++;
            print_node(jobs, option);
        }
        jobs = jobs->next;
    }
    if (argv[i])
    {
        ft_putstr_fd("42sh: no such jobs id ", 2);
        ft_putendl_fd(argv[i], 2);
        return (1);//exit failure
    }
    return (0);//exit seccuss
}