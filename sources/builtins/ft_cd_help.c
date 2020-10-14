/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 19:42:26 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/15 22:06:25 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*mod_path(char *path)
{
	int		i;
	char	*var;

	i = 0;
	if (!path)
		path = ft_getintern("HOME");
	else
	{
		ft_strdel(&path);
		var = ft_getintern("OLDPWD");
		if (var)
			return (var);
	}
	return (path);
}

static char	*remplace_point(char *pwd, char *path)
{
	int		len;
	char	*str;

	path++;
	len = ft_strlen(pwd) + ft_strlen(path);
	str = ft_strnew(len);
	str = ft_strcpy(str, pwd);
	str = ft_strcat(str, path);
	ft_strdel(&pwd);
	ft_strdel(&path);
	return (str);
}

static char	*replace_2point(char *pwd, char *path)
{
	char	*str;
	char	*last_pwd;
	int		len;
	int		i;

	path += 2;
	i = 0;
	last_pwd = ft_strrchr(pwd, '/');
	len = ft_strlen(pwd) + ft_strlen(path);
	str = ft_strnew(len);
	while (pwd[i])
	{
		if (!ft_strcmp(last_pwd, pwd + i))
			break ;
		str[i] = pwd[i];
		i++;
	}
	if (!str[0])
		str[0] = '/';
	str = ft_strcat(str, path);
	ft_strdel(&pwd);
	return (str);
}

char		*mod_point(char *path)
{
	int		i;
	char	*pwd;
	char	*tmp;

	i = 0;
	pwd = ft_strdup(g_pwd);
	if (!pwd)
		return (path);
	if (path[0] == '.' && path[1] == '\0')
	{
		ft_strdel(&path);
		return (pwd);
	}
	if (path[0] == '.' && path[1] == '/')
		return (remplace_point(pwd, path));
	if (path[0] == '.' && path[1] == '.' && (path[2] == '\0' || path[2] == '/'))
	{
		tmp = replace_2point(pwd, path);
		ft_strdel(&path);
		return (tmp);
	}
	ft_strdel(&pwd);
	return (path);
}

char		*get_all_path(char *path)
{
	char	*pwd;
	char	*str;

	pwd = ft_getintern("CDPATH");
	if (pwd)
	{
		str = get_cdpath(pwd, path);
		if (str)
		{
			free(path);
			return (str);
		}
	}
	pwd = g_pwd;
	if (pwd)
	{
		str = ft_strnew(ft_strlen(path) + ft_strlen(pwd) + 1);
		str = ft_strcpy(str, pwd);
		str = ft_strcat(str, "/");
		str = ft_strcat(str, path);
		free(path);
		return (str);
	}
	return (path);
}
