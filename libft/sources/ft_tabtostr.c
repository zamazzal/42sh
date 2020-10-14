/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabtostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:47:06 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 18:47:51 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_tabtostr(char **tab)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (tab[i])
	{
		if (i && !ft_strequ(tab[i], "") && !ft_strequ(tab[i], "&")
			&& !ft_strequ(tab[i], "|") && !ft_strequ(tab[i], ";"))
			str = ft_jandf(str, " ", 1, 0);
		str = ft_jandf(str, tab[i], 1, 0);
		i++;
	}
	dfre(tab);
	return (str);
}
