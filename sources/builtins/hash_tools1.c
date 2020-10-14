/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:38:55 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/07 12:44:56 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

unsigned long	hash_calc(char *str)
{
	int				i;
	unsigned long	hash;

	i = 0;
	hash = 5381;
	while (str[i] != '\0')
	{
		hash = ((hash << 5) + hash) + str[i];
		i++;
	}
	return (hash % HTABLE_SIZE);
}

char			*ft_getcmd_from_htab(char *cmd)
{
	unsigned long	hash;

	hash = hash_calc(cmd);
	if (g_htable[hash])
	{
		if (ft_strequ(g_htable[hash]->cmd, cmd))
		{
			if (access(g_htable[hash]->content, F_OK | X_OK) == 0)
			{
				g_htable[hash]->hits++;
				return (strdup(g_htable[hash]->content));
			}
		}
	}
	return (NULL);
}

int				ft_htab_addhit(char *cmd)
{
	unsigned long	hash;

	if (!cmd)
		return (1);
	hash = hash_calc(cmd);
	if (g_htable[hash])
		(g_htable[hash]->hits)++;
	return (0);
}

void			ft_freeh_htab(void)
{
	int			i;

	i = 0;
	while (i < HTABLE_SIZE)
	{
		if (g_htable[i])
		{
			ft_strdel(&g_htable[i]->cmd);
			ft_strdel(&g_htable[i]->content);
			free(g_htable[i]);
			g_htable[i] = NULL;
		}
		i++;
	}
}
