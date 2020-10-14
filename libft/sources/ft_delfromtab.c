/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delfromtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:11:49 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/12 18:48:34 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_delfromtab(char **tab, int index)
{
	char	**new_tab;
	int		len_tab;
	int		i;
	int		j;

	len_tab = ft_tablen(tab);
	new_tab = (char **)ft_mmalloc(sizeof(char *) * len_tab);
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (i != index)
		{
			new_tab[j] =
				(char *)ft_mmalloc(sizeof(char) * (ft_strlen(tab[i]) + 1));
			new_tab[j] = ft_strcpy(new_tab[j], tab[i]);
			j++;
		}
		i++;
	}
	dfre(tab);
	new_tab[j] = 0;
	return (new_tab);
}
