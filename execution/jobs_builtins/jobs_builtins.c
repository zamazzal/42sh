/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:04:05 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/19 01:51:39 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

//jobs [nbr] ...
//      -c : choix [nbr]
//      -l : list all avaible jobs (par defaut)
//      -r : list all jobs runing in the background
//      -s : list all jobs stopped.
//      -p : list all jobs pid.

// #define FLAGS_C
// #define FLAGS_L
// #define FLAGS_B
// #define FLAGS_S
// #define FLAGS_P

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
            if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
                (*option) |= get_type(argv[i][j] - 96);
            else if (argv[i][j] != '-')
            {
                jobs_usage(argv[i][j]);
                return (-1);
            }
            else if (argv[i][j] == '-')
                return (i + 1);
            j++;
        }
    }
    return (i);
}

// t_parse *get_jobs_cmd(c)

int     jobs_builtin(char **argv, t_objet *objet)
{
    t_jobs      *jobs;
    size_t      i;
    int         option = 0;

    if ((i = get_option(argv, &option)))
        return (1);//exit failure
    if (!objet->lst_jobs)
        return (0);//exit Seccuss
    jobs = objet->lst_jobs;
    while (jobs)
    {
        //if (!print_jobs(jobs, objet, &argv[i], option))
        //  i++;
        ft_putchar('[');
        ft_putnbr(jobs->proc_nbr);
        ft_putchar(']');
        (jobs->mode & IS_SELECTED) > 0 ? ft_putchar('+') : ft_putchar('-');
        ft_putstr(" ");
        (jobs->mode & IS_SUSPEND) > 0 ? ft_putstr("suspend") : ft_putstr("running");
        jobs = jobs->next;
    }
    return (0);//exit seccuss
}

// void showbits( unsigned int x )
// {
//     for (int i = (sizeof(int) * 8) - 1; i >= 0; i--)
//        putchar(x & (1u << i) ? '1' : '0');
//     printf("\n");
// }

// int main()
// {
//     char *av[] = {"cmd", "-abcAdef", NULL};
//     int option = 0;

//     get_option(av, &option);
//     showbits(option);
// }