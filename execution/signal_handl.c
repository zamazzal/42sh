/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 23:38:52 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/20 14:55:01 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

t_objet **save_objet(void)
{
    static t_objet *objet;

    return (&objet);
}

void    sig_handl(int sig)
{
    t_objet *objet;

    objet = *save_objet();
    if (sig == SIGINT || sig == SIGTSTP)
        ft_putendl("\n\033[1;36m42sh> \033[0m");
    if (sig == SIGCHLD)
        check_lstjobs(objet);
}

void sig_init(void)
{
    signal(SIGCHLD, sig_handl);
    signal(SIGTSTP, sig_handl);
    signal(SIGINT, sig_handl);
}