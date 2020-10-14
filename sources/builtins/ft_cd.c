/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 16:30:44 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/15 22:02:38 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	ft_2putstr(char *str, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(str2, 2);
}

static int	cderror(char *path)
{
	struct stat	buf;

	if (lstat(path, &buf) != -1)
	{
		if (!S_ISDIR(buf.st_mode) && !S_ISLNK(buf.st_mode))
		{
			ft_2putstr(path, ": Is not a Directory.");
			return (-1);
		}
	}
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
		{
			ft_2putstr(path, ": Permission denied.");
			return (-1);
		}
		return (0);
	}
	else
		ft_2putstr(path, ": No such file or directory.");
	return (-1);
}

static int	ft_cd_p(char *path, char *pwd)
{
	if (!path)
	{
		free(pwd);
		ft_putendl_fd("42sh : variable HOME doesnt set on env.", 2);
		return (1);
	}
	if (cderror(path) < 0)
	{
		free(path);
		free(pwd);
		return (1);
	}
	else
		chdir(path);
	ft_setenv("OLDPWD", g_pwd);
	getcwd(pwd, 4096);
	ft_setenv("PWD", pwd);
	ft_strdel(&path);
	ft_strdel(&g_pwd);
	g_pwd = pwd;
	return (0);
}

static int	ft_cd_l(char *path, char *pwd)
{
	if (!path)
	{
		ft_strdel(&pwd);
		ft_putendl_fd("42sh : variable doesnt set on env.", 2);
		return (1);
	}
	if (cderror(path) < 0)
	{
		ft_strdel(&path);
		ft_strdel(&pwd);
		return (1);
	}
	else
		chdir(path);
	ft_strcpy(pwd, path);
	ft_setenv("OLDPWD", g_pwd);
	ft_setenv("PWD", pwd);
	ft_strdel(&path);
	ft_strdel(&g_pwd);
	g_pwd = pwd;
	return (0);
}

int			ft_cd(char **args)
{
	int			opt[3];
	int			i;
	char		*pwd;
	char		*path;
	int			ret;

	i = 1;
	pwd = ft_strnew(4096);
	if (ft_cd_options(opt, &i, args) != 0)
		return (1);
	path = ft_strdup(args[i]);
	if (!args[i] || (args[i][0] == '-' && args[i][1] == '\0'))
		path = ft_strdup(mod_path(path));
	if (opt[0] == 1)
		ret = ft_cd_p(path, pwd);
	else
	{
		if (path && path[0] == '.')
			path = mod_point(path);
		if (path && path[0] != '/')
			path = get_all_path(path);
		ret = ft_cd_l(path, pwd);
	}
	return (ret);
}
