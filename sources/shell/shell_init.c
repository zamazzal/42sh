/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:52:36 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/15 04:00:00 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ret_tab_toline(char *line)
{
	int i;

	i = -1;
	while (line[++i])
		if (line[i] < 0)
			line[i] = '\t';
}

void		sigs(void)
{
	g_ctrl_csig = 1;
	g_ctrl_dsig = 0;
	g_line_type = 0;
}

void		ft_saveinhistory(char *cmd)
{
	char **argv;

	if (!cmd)
		return ;
	if (!(argv = clear_quots(ft_cmdsplit(cmd, ' '))))
		return ;
	if (!ft_strequ(argv[0], "fc"))
	{
		ft_savein_file(cmd);
		ft_add_history(&cmd);
	}
	ft_freetable(&argv);
}
