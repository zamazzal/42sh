/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_instr_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:21:31 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/16 02:28:59 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	*ms_expand_dollarone(char *arg)
{
	int		i;
	int		quoted;
	char	quote;
	char	*result;

	result = ft_strnew(0);
	quoted = FALSE;
	i = 0;
	while (arg[i])
	{
		ms_set_quote(&quoted, &quote, arg[i]);
		if (arg[i] == '$')
		{
			if ((quoted == TRUE && quote == DQ) || (quoted == FALSE))
			{
				i++;
				i += ms_expand_dollar(&result, arg + i);
				continue ;
			}
		}
		ft_strappend(&result, arg[i], TRUE);
		i++;
	}
	return (result);
}

char		*ms_expand_arg(char *arg)
{
	char	*result;
	char	*tmp;

	result = ms_expand_dollarone(arg);
	tmp = ft_strdup(result);
	ft_strdel(&result);
	result = ms_expand_quotes(tmp);
	ft_strdel(&tmp);
	return (result);
}

char		**ft_prepar(char **str)
{
	char	**argv;
	char	*tmp;
	int		i;

	argv = ft_cmdsplit(*str, ' ');
	i = 0;
	while (argv[i])
	{
		tmp = argv[i];
		argv[i] = ms_expand_arg(argv[i]);
		ft_strdel(&tmp);
		i++;
	}
	return (argv);
}

int			setervars(char **str)
{
	char	**argv;
	int		i;

	i = 0;
	argv = ft_prepar(str);
	if (check_var_ster(argv[0]))
	{
		ft_freetable(&argv);
		return (1);
	}
	if (!ft_check_var_temp(ft_tablen(argv), argv))
	{
		while (argv[i])
			ft_seter2(argv[i++]);
	}
	else
	{
		ft_freetable(&argv);
		return (1);
	}
	ft_strdel(str);
	ft_freetable(&argv);
	*str = ft_strdup("true");
	return (0);
}
