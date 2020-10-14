/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_tag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:14:49 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/16 03:34:06 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_issetornull(char *variablename,
							int tag, char **arg)
{
	ft_strdel(arg);
	*arg = ft_strdup(ft_getintern(variablename));
	if (*arg == NULL || ft_strequ(*arg, ""))
	{
		if (tag == EQUAL && ft_strequ(*arg, ""))
		{
			*arg = ft_strjoin(variablename, "=");
			g_intern = ft_delfromtab(g_intern,
						ft_aliasexist(*arg, g_intern));
		}
		ft_strdel(arg);
		return (0);
	}
	if (tag == PLUS)
		ft_strdel(arg);
	return (1);
}

static void	ft_condition(char **arg, char *splitted)
{
	char	*tmp;

	tmp = *arg;
	*arg = ft_strequ(splitted, "") ? NULL : ft_strdup(splitted);
	ft_strdel(&tmp);
}

void		ft_splitytags(char **splitted, int *tag, char **arg)
{
	int		isset;
	char	*tmp;

	isset = ft_issetornull(splitted[0], *tag, arg);
	if (!*arg && (*tag == EQUAL || *tag == MINCE ||
					*tag == INTEROGATION || *tag == PLUS))
	{
		if (isset || (!isset && (*tag == EQUAL || *tag == MINCE)))
			ft_condition(arg, splitted[1]);
		tmp = ft_jandf(ft_strjoin(splitted[0], "="), splitted[1], 1, 0);
		if (!isset && *tag == EQUAL)
			g_intern = ft_addtotab(g_intern, tmp);
		else if (*tag == INTEROGATION)
		{
			ft_putstr_fd("42sh : ", 2);
			ft_putstr_fd(splitted[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(splitted[1], 2);
			*tag = ERROR_STOP;
		}
		ft_strdel(&tmp);
	}
	ft_hashmodulus(splitted, tag, arg);
}

void		ft_hashmodulus(char **splitted, int *tag, char **arg)
{
	char	*tmp;
	int		i;

	if (*arg && (*tag == TWO_HASH || *tag == END_HASH) &&
			(tmp = ft_strnstr(*arg, splitted[1], ft_strlen(splitted[1]))))
	{
		tmp = ft_strdup(tmp + ft_strlen(splitted[1]));
		ft_strdel(arg);
		*arg = tmp;
	}
	else if (*arg && (*tag == TWO_MODULO || *tag == MODULO) &&
				ft_strlen(*arg) >= ft_strlen(splitted[1]))
	{
		i = ft_strlen(*arg) - ft_strlen(splitted[1]);
		if (ft_strequ(*arg + i, splitted[1]))
		{
			tmp = ft_strsub(*arg, 0, i);
			ft_strdel(arg);
			*arg = tmp;
		}
	}
}

void		ft_starthash(char **arg, int *tag)
{
	char	*value;

	if ((*arg)[1] == '#')
	{
		ft_strdel(arg);
		*arg = ft_strdup("0");
	}
	else
	{
		ft_badsubstitutiondetector(*arg + 1, tag);
		if (*tag != ERROR)
		{
			if ((value = ft_getintern(*arg + 1)))
			{
				ft_strdel(arg);
				*arg = ft_strdup(ft_itoa(ft_strlen(value)));
			}
			else
			{
				ft_strdel(arg);
				*arg = ft_strdup("0");
			}
		}
	}
}
