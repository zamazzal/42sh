/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:53:03 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/14 18:53:09 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"


//// joinlite and ft_getenv









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

static void	ft_flagerror(char c)
{
	ft_putstr_fd("hash: -", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("usage: hash [-r] [name ...]", 2);
}

static int	ft_getflags(int argc, char **argv, int *mode)
{
	int		i;
	int		j;
	int		x;

	*mode = 0;
	i = 1;
	x = 0;
	while (i < argc && argv[i][0] == '-' && ft_isprint(argv[i][1])
	&& !ft_strequ(argv[i], "--"))
	{
		j = 1;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == 'r')
				*mode = 1;
			else
			{
				ft_flagerror(argv[i][j]);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (i);
}




static char		*ft_getcmd_from_htab(char *cmd)
{
	unsigned long	hash;
	t_hashtable		*tmp;

	hash = hash_calc(cmd);
	tmp = g_hash.htable[hash];
	while (tmp)
	{
		if (ft_strequ(tmp->cmd, cmd))
		{
			tmp->hits++;
			return (strdup(tmp->content));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void			ft_freeh_htab(void)
{
	int			i;
	t_hashtable	*tmp;

	i = 0;
	while (i <= HTABLE_SIZE)
	{
		if (g_hash.htable[i])
		{
			while (g_hash.htable[i])
			{
				tmp = g_hash.htable[i];
				ft_strdel(&g_hash.htable[i]->cmd); // strdel
				ft_strdel(&g_hash.htable[i]->content); // strdel
				g_hash.htable[i] = g_hash.htable[i]->next;
				free(tmp);
			}
		}
		i++;
	}
}


int		hash()
{
	int	n;
	t_hashtable	*tmp;
	int i;

	i = 0;
	
	n = 0;
	while (i <= HTABLE_SIZE)
	{
		if (g_hash.htable[i])
		{
			if (n == 0)
			{
				ft_putendl("hits\tcommand");
				n++;
			}
			tmp = g_hash.htable[i];
			while (tmp)
			{
				ft_putnbr(tmp->hits);
				ft_putchar('\t');
				ft_putendl(tmp->content); // strdel
				tmp = tmp->next;
			}
		}
		i++;
	}
	if (!n)
		ft_putendl("hash: hash table empty");
	return (0);
}

static int		ft_putin_htab(char *cmd, char *path)
{
	unsigned long	hash;
	t_hashtable		*tmp;

	if (!cmd)
		return (0);
	hash = hash_calc(cmd);
	tmp = g_hash.htable[hash];
	while (g_hash.htable[hash])
	{
		if (ft_strequ(g_hash.htable[hash]->cmd, cmd))
			return (0);
		g_hash.htable[hash] = g_hash.htable[hash]->next;
	}
	SAFE(g_hash.htable[hash] = (t_hashtable*)malloc(sizeof(t_hashtable)));
	g_hash.htable[hash]->cmd = ft_strdup(cmd);
	g_hash.htable[hash]->content = ft_strdup(path);
	g_hash.htable[hash]->hits = 0;
	g_hash.htable[hash]->next = NULL;
	if (tmp)
		g_hash.htable[hash] = tmp;
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
				real = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
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

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (!(path = getenv("PATH")))
		return (NULL);
	if (!(paths = ft_strsplit(path, ':')))
		return (NULL);
	rzlt = ft_getcmd(cmd, paths);
	//ft_freetable(&paths);
	return (rzlt);
}


static int		ft_add_inhashtable(char *cmd, char *path)
{
	unsigned long	hash;
	t_hashtable		*tmp;

	if (!cmd)
		return (1);
	hash = hash_calc(cmd);
	tmp = g_hash.htable[hash];
	while (g_hash.htable[hash])
	{
		if (ft_strequ(g_hash.htable[hash]->cmd, cmd))
		{
			ft_strdel(&g_hash.htable[hash]->cmd);
			ft_strdel(&g_hash.htable[hash]->content);
			free(g_hash.htable[hash]);
			break ;
		}
		g_hash.htable[hash] = g_hash.htable[hash]->next;
	}
	SAFE(g_hash.htable[hash] = (t_hashtable*)malloc(sizeof(t_hashtable)));
	g_hash.htable[hash]->cmd = ft_strdup(cmd);
	g_hash.htable[hash]->content = ft_strdup(path);
	g_hash.htable[hash]->hits = 0;
	if (!g_hash.htable[hash]->next)
		g_hash.htable[hash]->next = NULL;
	if (tmp)
		g_hash.htable[hash] = tmp;
	return (0);
}

int	ft_sethash(char **argv)
{
	int rtn;
	char *cmd;
	int i;

	i = 0;
	rtn = 0;
	while (argv[i])
	{
		cmd = ft_checkcmd(argv[i]);
		if (!cmd)
		{
			rtn = 1;
			ft_putstr_fd("hash: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putendl_fd(": not found", 2);
		}
		else
			ft_add_inhashtable(argv[i], cmd);
		i++;
	}
	return (rtn);
}

int	ft_hash(int argc, char **argv)
{
	int mode;
	int i;

	i = ft_getflags(argc, argv, &mode);
	if (i == -1)
		return (2);
	if (argc > 1)
	{
		if (mode)
			ft_freeh_htab();
		return (ft_sethash(&argv[i]));
	}
	else
		hash();
	return (0);
}


int main(int argc, char **argv)
{

	char *cmd;



	ft_putin_htab("ls", "/bin/ls");
	ft_putin_htab("lsx", "/bin/lsx");
	ft_hash(argc, argv);
	hash();
	return (0);
	exit(0);
	ft_putin_htab("ls", "/bin/ls");
	ft_putin_htab("ls", "/bin/ls");
	cmd = ft_getcmd_from_htab("ls");
	ft_putendl("xxxxxxxx");
	ft_putendl(cmd);
	ft_putendl("xxxxxxxx");
	ft_putin_htab("ls1", "/bin/ls5");
	hash();
	ft_freeh_htab();
}