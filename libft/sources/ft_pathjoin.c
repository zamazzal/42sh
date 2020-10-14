/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:07:24 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/09 20:31:15 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char *path, char *dossier)
{
	char	*tmp;
	char	*newpath;
	int		i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 1] != '/')
	{
		if (!(tmp = ft_strjoin(path, "/")))
			exit(EXIT_FAILURE);
	}
	else
		tmp = ft_strdup(path);
	if (!(newpath = ft_strjoin(tmp, dossier)))
		exit(EXIT_FAILURE);
	ft_strdel(&tmp);
	return (newpath);
}
