/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 12:37:55 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/07 12:38:07 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_return2(int r)
{
	return (r == 0 ? 0 : 1);
}

static int	ft_checktype(struct stat buf, char *flag)
{
	if (!ft_strcmp(flag, "-b"))
		return (ft_return(S_ISBLK(buf.st_mode)));
	if (!ft_strcmp(flag, "-c"))
		return (ft_return(S_ISCHR(buf.st_mode)));
	if (!ft_strcmp(flag, "-d"))
		return (ft_return(S_ISDIR(buf.st_mode)));
	if (!ft_strcmp(flag, "-e"))
		return (0);
	if (!ft_strcmp(flag, "-f"))
		return (ft_return(S_ISREG(buf.st_mode)));
	if (!ft_strcmp(flag, "-L"))
		return (ft_return(S_ISLNK(buf.st_mode)));
	if (!ft_strcmp(flag, "-p"))
		return (ft_return(S_ISFIFO(buf.st_mode)));
	if (!ft_strcmp(flag, "-S"))
		return (ft_return(S_ISSOCK(buf.st_mode)));
	return (2);
}

static int	ft_checkperm(char *path, char *flag)
{
	if (!ft_strcmp(flag, "-r"))
		return (ft_return2(access(path, R_OK)));
	if (!ft_strcmp(flag, "-w"))
		return (ft_return2(access(path, W_OK)));
	if (!ft_strcmp(flag, "-x"))
		return (ft_return2(access(path, X_OK)));
	return (2);
}

static int	ft_checkdetails(struct stat buf, char *flag)
{
	if (!ft_strcmp(flag, "-s"))
		return (buf.st_size > 0 ? 0 : 1);
	if (!ft_strcmp(flag, "-u"))
		return (ft_return(buf.st_mode & S_ISUID));
	if (!ft_strcmp(flag, "-g"))
		return (ft_return(buf.st_mode & S_ISGID));
	return (2);
}

int			ft_test(char *name, char *flag)
{
	struct stat buf;
	int			r;

	lstat(name, &buf);
	if ((r = ft_checktype(buf, flag)) != 2)
		return (r);
	if ((r = ft_checkperm(name, flag)) != 2)
		return (r);
	if ((r = ft_checkdetails(buf, flag)) != 2)
		return (r);
	return (ft_type_error(flag, ": unary operator expected"));
}
