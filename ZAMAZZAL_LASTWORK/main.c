#include "mysh.h"


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
	return (0);
}

int main()
{
    char	*line;
	int i;

    ft_setterm();
    creation();
	i = 0;
    while (1)
	{
		line = ft_readline("mysh$> \n");





		
		ft_savein_file(line);
		ft_add_history(&line);
		if (i == 5)
			return (0);
		i++;
		ft_strdel(&line);
	}
    return (0);
}