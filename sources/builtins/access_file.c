/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:33:36 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/09 20:49:35 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	**my_paths(char **env)
{
	int		i;
	char	**tab1;

	i = 0;
	tab1 = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH=") != NULL)
			tab1 = ft_strsplit(ft_strstr(env[i], "/"), ':');
		i++;
	}
	return (tab1);
}

char	*access_file(char **env, char *file)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = 0;
	if ((file[0] == '.' && file[1] == '/') ||
	!(paths = my_paths(env)))
		return (file);
	while (paths[i])
	{
		tmp = ft_pathjoin(paths[i], file);
		if (access(tmp, F_OK) == 0)
		{
			dfre(paths);
			return (tmp);
		}
		ft_strdel(&tmp);
		i++;
	}
	dfre(paths);
	return (file);
}
