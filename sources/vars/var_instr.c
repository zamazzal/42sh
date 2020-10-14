/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_instr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:30:26 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 22:27:25 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_maketmp(void)
{
	g_tmpmode = 1;
	g_tmpenv = g_environ;
	g_environ = ft_tabdup(g_tmpenv);
	g_tmpintern = g_intern;
	g_intern = ft_tabdup(g_tmpintern);
	return (1);
}

static char		*ft_createcmd(char **argv)
{
	char	*str;
	int		i;

	i = 0;
	if (!argv)
		return (NULL);
	while (argv[i])
	{
		if (i == 0)
			str = ft_strdup(argv[i]);
		else
			str = ft_strjoin_lite(ft_strjoin_lite(str, " "), argv[i]);
		i++;
	}
	return (str);
}

static	int		ft_checkiftmpvar(char **cmd, char ***args, int *i)
{
	char	*line;

	line = *cmd;
	if (!line)
		return (0);
	*i = 0;
	*args = clear_quots(ft_cmdsplit(line, ' '));
	if (check_var_ster((*args)[0]))
	{
		ft_freetable(args);
		return (1);
	}
	return (-1);
}

int				ft_settmpvar(char **cmd)
{
	char	**args;
	int		i;
	int		rtn;

	if ((rtn = ft_checkiftmpvar(cmd, &args, &i) != -1))
		return (rtn);
	if (ft_check_var_temp(ft_tablen(args), args))
	{
		ft_maketmp();
		while (args[i])
		{
			if (!check_var_ster(args[i]))
				ft_seter(args[i]);
			else
			{
				ft_strdel(cmd);
				*cmd = ft_createcmd(&args[i]);
				break ;
			}
			i++;
		}
	}
	ft_freetable(&args);
	return (0);
}

int				ft_endoftmp(int val)
{
	if (g_tmpmode == 1)
	{
		ft_freetable(&g_environ);
		ft_freetable(&g_intern);
		g_environ = g_tmpenv;
		g_intern = g_tmpintern;
		g_tmpmode = 0;
	}
	return (val);
}
