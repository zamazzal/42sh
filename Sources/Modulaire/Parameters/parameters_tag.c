/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_tag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:14:49 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/20 06:13:22 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/tildenparams.h"

char		*ft_getintern(const char *name, char **allparams)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	if (!name)
		return (NULL);
	env = ft_strjoin(name, "=");
	len = ft_strlen(env);
	while (allparams[i] != NULL)
	{
		if (ft_strnstr(allparams[i], env, len))
		{
			ft_strdel(&env);
			return (ft_strchr(allparams[i], '=') + 1);
		}
		i++;
	}
	ft_strdel(&env);
	return (NULL);
}

int			ft_issetornull(char *variablename, char ***allparams,
							int tag, char **arg)
{
	*arg = ft_strdup(ft_getintern(variablename, *allparams));
	if (*arg == NULL || ft_strequ(*arg, ""))
	{
		if (tag == EQUAL && ft_strequ(*arg, ""))
		{
			*arg = ft_strjoin(variablename, "=");
			*allparams = ft_delfromtab(*allparams,
						ft_aliasexist(*arg, *allparams));
		}
		ft_strdel(arg);
		return (0);
	}
	if (tag == PLUS)
		ft_strdel(arg);
	return (1);
}

/**
 *	After this function check the out put
 *	if  return value == 0 means there is an error
 *	if arg == NULL means delete this node.
**/

void		ft_splitytags(char **splitted, int *tag,
								char ***allparams, char **arg)
{
	int		isset;

	isset = ft_issetornull(splitted[0], allparams, *tag, arg);
	if (!*arg && (*tag == EQUAL || *tag == MINCE ||
					*tag == INTEROGATION || *tag == PLUS))
	{
		if (isset || (!isset && (*tag == EQUAL || *tag == MINCE)))
			*arg = ft_strequ(splitted[1], "") ? NULL : ft_strdup(splitted[1]);
		if (!isset && *tag == EQUAL)
			*allparams = ft_addtotab(*allparams,
					ft_jandf(ft_strjoin(splitted[0], "="), splitted[1], 1, 0));
		else if (*tag == INTEROGATION)
		{
			ft_putstr_fd("42sh : ", 2);
			ft_putstr_fd(splitted[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(splitted[1], 2);
			*tag = ERROR_STOP;
		}
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

void		ft_starthash(char **arg, char **allparams, int *tag)
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
			if ((value = ft_getintern(*arg + 1, allparams)))
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
