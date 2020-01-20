/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:19:53 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/20 06:36:15 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/mysh_zamazzal.h"

static int		ft_type_error(char *s1, char *s2)
{
	ft_putstr_fd("test: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(s2, 2);
	return (2);
}

int		ft_return(int r)
{
	return (r != 0 ? 0 : 1);
}

int		ft_return2(int r)
{
	return (r == 0 ? 0 : 1);
}

int	ft_checktype(struct stat buf, char *flag)
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

int	ft_checkperm(char *path, char *flag)
{
	if (!ft_strcmp(flag, "-r"))
		return (ft_return2(access(path, R_OK)));
	if (!ft_strcmp(flag, "-w"))
		return (ft_return2(access(path, W_OK)));
	if (!ft_strcmp(flag, "-x"))
		return (ft_return2(access(path, X_OK)));
	return (2);
}

int	ft_checkdetails(struct stat buf, char *flag)
{
	if (!ft_strcmp(flag, "-s"))
		return (buf.st_size > 0 ? 0 : 1);
	if (!ft_strcmp(flag, "-u"))
		return (ft_return(buf.st_mode & S_ISUID));
	if (!ft_strcmp(flag, "-g"))
		return (ft_return(buf.st_mode & S_ISGID));
	return (2);
}

int		ft_test(char *name, char *flag)
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

int	ft_test2args(char **argv)
{
	if (ft_strcmp(argv[0], "-z") == 0)
		return (ft_strlen(argv[0]) ? 1 : 0);
	if (!access(argv[1], F_OK))
		return (ft_test(argv[1], argv[0]));
	return (1);
}

int		ft_testreturn(int rtn, int mode)
{
	if (mode == 1)
		return (rtn == 1 ? 0 : 1);
	return (rtn);
}

int		ft_checkop(char *str)
{
	if (!ft_strcmp(str, "-eq"))
		return (1);
	if (!ft_strcmp(str, "-ne"))
		return (2);
	if (!ft_strcmp(str, "-gt"))
		return (3);
	if (!ft_strcmp(str, "-ge"))
		return (4);
	if (!ft_strcmp(str, "-lt"))
		return (5);
	if (!ft_strcmp(str, "-le"))
		return (6);
	return (-1);
}

int		ft_checknbr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_checkcalc(char *arg1, int r, char *arg2)
{
	int num1;
	int num2;

	num1 = ft_atoi(arg1);
	num2 = ft_atoi(arg2);
	if (r == 1)
		return (num1 == num2 ? 0 : 1);
	if (r == 1)
		return (num1 == num2 ? 0 : 1);
	if (r == 2)
		return (num1 != num2 ? 0 : 1);
	if (r == 3)
		return (num1 > num2 ? 0 : 1);
	if (r == 4)
		return (num1 >= num2 ? 0 : 1);
	if (r == 5)
		return (num1 < num2 ? 0 : 1);
	if (r == 6)
		return (num1 <= num2 ? 0 : 1);
	return (1);
}

int		ft_test3args(char **argv)
{
	int r;

	if (!ft_strcmp(argv[1], "="))
		return (ft_strcmp(argv[0], argv[2]));
	if (!(ft_strcmp(argv[1], "!=")))
		return (ft_return(ft_strcmp(argv[0], argv[2])));
	if ((r = ft_checkop(argv[1])) != -1)
	{
		if (ft_checknbr(argv[0]))
			return (ft_type_error(argv[0], ": integer expression expected"));
		if (ft_checknbr(argv[2]))
			return (ft_type_error(argv[2], ": integer expression expected"));
		return (ft_checkcalc(argv[0], r, argv[2]));
	}
	ft_type_error(argv[1], ": unary operator expected");
	return (2);
}

int		ft_testerror(void)
{
	ft_putendl_fd("test: too many arguments", 2);
	return (2);
}

int		test(int argc, char **argv)
{
	int mode;

	mode = 0;
	if (argc >= 3)
	{
		if (!ft_strcmp(argv[1], "!"))
		{
			argc--;
			argv = &argv[2];
			mode = 1;
		}
		else
			argv = &argv[1];
	}
	if (argc == 2)
		return (ft_testreturn(!argv[0] ? 1 : 0, mode));
	else if (argc == 3)
		return (ft_testreturn(ft_test2args(&argv[0]), mode));
	else if (argc == 4)
		return (ft_testreturn(ft_test3args(argv), mode));
	else if (argc > 4)
		return (ft_testerror());
	return (ft_testreturn(1, mode));
}
