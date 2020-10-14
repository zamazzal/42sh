/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:04:54 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/09 20:38:12 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*get_cdpath(char *pwd, char *path)
{
	char	**paths;
	int		i;
	char	*tmp;

	i = 0;
	paths = ft_strsplit(pwd, ':');
	while (paths[i])
	{
		tmp = ft_pathjoin(paths[i], path);
		if (!access(tmp, X_OK))
		{
			dfre(paths);
			return (tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	return (NULL);
}
