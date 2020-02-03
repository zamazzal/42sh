/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   main_test.c                                       :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: sopu <sopu@student.1337.ma>                   +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: Invalid date        by                 #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2020/02/02 14:46:55 by sopu         ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

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
		all_aliases = (char **)ft_mmalloc(sizeof(char *) * 4);
		all_aliases[0] = ft_strdup("a='b'");
		all_aliases[1] = ft_strdup("b='a'");
		all_aliases[2] = ft_strdup("c='bye'");
		all_aliases[3] = 0;
		if (ft_strequ(gv[1], "alias"))
			alias(allocategv, &all_aliases);
		else if (ft_strequ(gv[1], "unalias"))
			unalias(allocategv, &all_aliases);
		else
		{
			tmp = ft_strdup(gv[1]);
			ft_replacealiass(&tmp, all_aliases);
			printf("\n ALIASS == |---%s---| \n", tmp);
		}
	}
}
