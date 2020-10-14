/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:36:56 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 22:38:13 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_freetable(char ***array)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_tablen(*array);
	while (i < size)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	(*array) = NULL;
}

char	**ft_jointab(char **tab1, char **tab2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	**new;

	i = 0;
	j = 0;
	len1 = ft_tablen(tab1);
	len2 = ft_tablen(tab2);
	SAFE(new = (char **)ft_mmalloc(sizeof(char*) * (len1 + len2 + 1)));
	while (tab1[i] != NULL)
		new[j++] = ft_strdup(tab1[i++]);
	i = 0;
	while (tab2[i] != NULL)
		new[j++] = ft_strdup(tab2[i++]);
	new[j] = NULL;
	ft_freetable(&tab1);
	return (new);
}
