/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 23:38:52 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/12 01:57:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	sig_handl(int sig)
{
	if (sig == SIGINT)
		ft_putendl("\n42sh>");
	if (sig == SIGCHLD)
		check_lstjobs();
}

void	sig_init(void)
{
	signal(SIGTTIN, sig_handl);
	signal(SIGTTOU, sig_handl);
	signal(SIGTSTP, sig_handl);
	signal(SIGCHLD, sig_handl);
	signal(SIGTSTP, sig_handl);
	signal(SIGINT, sig_handl);
}
