/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:39:05 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/14 14:09:07 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_add_inhashtable(char *cmd, char *path)
{
	unsigned long	hash;

	if (!cmd)
		return (1);
	hash = hash_calc(cmd);
	if (g_htable[hash])
	{
		if (g_htable[hash]->cmd)
			ft_strdel(&g_htable[hash]->cmd);
		if (g_htable[hash]->content)
			ft_strdel(&g_htable[hash]->content);
		free(g_htable[hash]);
		g_htable[hash] = NULL;
	}
	SAFE(g_htable[hash] = (t_hashtable*)ft_mmalloc(sizeof(t_hashtable)));
	g_htable[hash]->cmd = ft_strdup(cmd);
	g_htable[hash]->content = ft_strdup(path);
	g_htable[hash]->hits = 0;
	return (0);
}

static char		*ft_getcmd(char *cmd, char **paths)
{
	char			*real;
	DIR				*dir;
	int				i;
	struct dirent	*name;

	i = 0;
	real = NULL;
	while (paths[i] != NULL && !real)
	{
		dir = opendir(paths[i]);
		if (dir == NULL)
		{
			i++;
			continue;
		}
		while ((name = readdir(dir)) && !real)
		{
			if (ft_strequ(cmd, name->d_name))
				real = ft_strjoin_lite(ft_strjoin(paths[i], "/"), cmd);
		}
		closedir(dir);
		i++;
	}
	return (real);
}

char			*ft_checkcmd(char *cmd)
{
	char *path;
	char **paths;
	char *rzlt;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	if (!(path = ft_getintern("PATH")))
		return (NULL);
	if (!(paths = ft_strsplit(path, ':')))
		return (NULL);
	rzlt = ft_getcmd(cmd, paths);
	ft_freetable(&paths);
	return (rzlt);
}

int				ft_clearhash(void)
{
	int i;

	i = 0;
	while (i < HTABLE_SIZE)
	{
		if (g_htable[i])
		{
			g_htable[i]->cmd = NULL;
			g_htable[i]->content = NULL;
			g_htable[i]->hits = 0;
		}
		g_htable[i] = NULL;
		i++;
	}
	return (0);
}
