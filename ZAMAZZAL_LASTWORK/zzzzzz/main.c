#include "includes/exec.h"


static void		ft_create_default_vars(void)
{
	ft_setitern("ZAMAZZAL1", "zamazzal");
	ft_setitern("ZAMAZZAL2", "zamazzal");
	ft_setitern("ZAMAZZAL3", "zamazzal");
	ft_setitern("ZAMAZZAL4", "zamazzal");
}

int				creation(void)
{
	extern char	**environ;
	char		*shlvl;

	ft_setterm();
    g_readline = (t_read *)malloc(sizeof(t_read));
    ft_load_history();
	SAFE(g_intern = (char **)malloc(sizeof(char *)));
	g_intern[0] = NULL;
	ft_create_default_vars();
	g_environ = ft_tabdup(environ);
	shlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1);
	ft_setenv("SHLVL", shlvl);
	ft_strdel(&shlvl);
	g_intern = ft_jointab(g_intern, g_environ);
    ft_puttables(environ);
	return (0);
}

int main()
{
    t_objet     **objet;
    char        *line;
    char        *tmp;

    sig_init();
    creation();
    objet = save_objet();
    if (!(*objet = (t_objet*)ft_memalloc(sizeof(t_objet))))
        return (ft_perror("42sh: malloc"));
    printf("hahowa >> %s\n", ft_getenv("PATH"));
    while (1)
    {
        if ((line = ft_readline("zamazzal$> \n")) > 0)
		{
			ft_putchar('\n');
			ft_putchar('\n');
            tmp = line;
            line = ft_strtrim(line);
            free(tmp);
            if (!ft_strncmp(line, "exit", 4))
            {
                free(line);
                return (0);
            }
            if (((*objet)->lst_parse = parse_lst(&line)))
            {
                printf("\n\t\t\t\tline ==> %s\n", (*objet)->lst_parse->cmd);
                ft_savein_file(line);
			    ft_add_history(&line);
                exec_lstparse(*objet);
            }
        }
        ft_strdel(&line);
        exit_parsing(&(*objet)->lst_parse , NULL, EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}