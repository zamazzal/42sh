/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 01:15:12 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/23 04:03:19 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expansion.h"

static void		ft_zaapsquote(char *cmd, int *i)
{
	*i++;
	while (cmd[*i] && cmd[*i] != 39)
		*i++;
}

void			ft_expansion(char **cmd)
{
	int			index;
	int			len;
	int			i;
	int			dquote;

	i = 0;
	dquote = 0;
	while (*cmd[i])
	{
		if (*cmd[i] == 39)
			ft_zaapsquote(*cmd, &i);
		else if (*cmd[i] == 34)
			if (dquote)
				dquote = 0;
			else
				dquote = 1;
		else if (*cmd[i] == '~' && !dquote && (i == 0 || *cmd[i - 1] < 33));
			// Change the tilde
		else if (*cmd[i] == '$');
			// Variable management
		i++;
	}
}
