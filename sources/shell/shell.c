/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:49:33 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/16 03:38:06 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void				ft_create_defaulvars(void)
{
	ft_setitern("status", "0");
}

static int				creation(void)
{
	extern char	**environ;
	char		*shlvl;

	g_all_aliases = NULL;
	g_jobs = NULL;
	g_tmpmode = 0;
	g_readline = (t_read *)ft_mmalloc(sizeof(t_read));
	g_intern = (char **)ft_mmalloc(sizeof(char *));
	g_intern[0] = NULL;
	ft_create_defaulvars();
	if (!(g_environ = ft_tabdup(environ)))
		return (-1);
	if (!(shlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1)))
		return (-1);
	ft_setenv("SHLVL", shlvl);
	ft_strdel(&shlvl);
	if (!(g_intern = ft_jointab(g_intern, g_environ)))
		return (-1);
	g_last_jobs_id = 1;
	g_shell_pid = getpid();
	if (!(g_ttyname = ft_strdup(ttyname(0))))
		return (-1);
	return (0);
}

static void				ft_initpaths(void)
{
	g_random_save = ft_strjoin(ft_getintern("HOME"), "/.42sh_random_save");
	g_history_saved = ft_strjoin(ft_getintern("HOME"), "/.42sh_history");
	if (!g_random_save || !g_history_saved)
		exit(EXIT_FAILURE);
}

static int				ft_initshell(void)
{
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_putstr_fd("42sh: (stdin/stdout) bad file descriptor\n", 2);
		exit(EXIT_FAILURE);
	}
	sig_init();
	ft_setterm();
	ft_clearhash();
	if ((creation() == -1))
		exit(EXIT_FAILURE);
	ft_initpaths();
	ft_load_history();
	g_pwd = ft_strdup(ft_getintern("PWD"));
	if (!g_pwd)
	{
		g_pwd = ft_strnew(4096);
		getcwd(g_pwd, 4096);
	}
	return (0);
}

int						main(void)
{
	t_parse		*lst;
	char		*line;
	char		*tmp;

	ft_initshell();
	while (1)
	{
		sigs();
		if ((line = ft_readline("42sh$> \n")))
		{
			ft_putchar('\n');
			check_lstjobs();
			tmp = line;
			line = ft_strtrim(line);
			ft_strdel(&tmp);
			replace_alias(&line);
			(lst = parse_lst(&line)) ? exec_lstparse(lst, 0)
			: ft_setstatus_var(258);
		}
		(line) ? ft_saveinhistory(line) : 0;
		ft_strdel(&line);
		exit_parsing(&lst, NULL, EXIT_FAILURE);
	}
	ft_strdel(&g_ttyname);
	exit(EXIT_SUCCESS);
}
