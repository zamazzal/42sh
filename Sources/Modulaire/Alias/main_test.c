/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:48:57 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/20 05:49:20 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/shell.h"
#include <stdio.h>

int			main(int gc, char **gv)
{
	int		i;
	char	**all_aliases;
	char	**loopdetector;
	char	**allocategv;
	char	*tmp;

	if (gc > 0)
	{
		allocategv = (char **)ft_mmalloc(sizeof(char *) * (gc + 1));
		i = 1;
		while (i < gc)
		{
			allocategv[i - 1] = ft_strdup(gv[i]);
			i++;
		}
		all_aliases = (char **)ft_mmalloc(sizeof(char *) * 3);
		all_aliases[0] = ft_strdup("a='b'");
		all_aliases[1] = ft_strdup("b='a'");
		all_aliases[2] = 0;
		if (ft_strequ(gv[1], "alias"))
			alias(allocategv, &all_aliases);
		else if (ft_strequ(gv[1], "unalias"))
			unalias(allocategv, &all_aliases);
		else
		{
			loopdetector = (char **)malloc(sizeof(char *));
			loopdetector[0] = 0;
			tmp = ft_getaliasvalue(ft_strdup(gv[1]), all_aliases, loopdetector);
			ft_putstr(tmp);
		}
		

		i = 0;
		while (all_aliases[i])
		{
			if (i == 0)
				ft_putstr("\n                  ALL ALIASES\n");
			ft_putstr("\nAll_aliases[");
			ft_putnbr(i);
			ft_putstr("] = |-- ");
			ft_putstr(all_aliases[i]);
			ft_putstr(" --|\n"); 
			i++;
		}
	}
}
