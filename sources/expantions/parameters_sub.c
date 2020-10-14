/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:53:52 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/04 13:07:06 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_specifytags(int i, char *param_arg, int *tag)
{
	if (i == 0)
	{
		ft_badsubstitution(param_arg, tag);
		return (-2);
	}
	i++;
	if (param_arg[i] == '+')
		*tag = PLUS;
	else if (param_arg[i] == '-')
		*tag = MINCE;
	else if (param_arg[i] == '?')
		*tag = INTEROGATION;
	else if (param_arg[i] == '=')
		*tag = EQUAL;
	else
	{
		ft_badsubstitution(param_arg, tag);
		return (-2);
	}
	return (i - 1);
}

void		ft_badsubstitution(char *param_arg, int *tag)
{
	ft_putstr_fd("42sh: ${", 2);
	ft_putstr_fd(param_arg, 2);
	ft_putstr_fd("}: bad substitution\n", 2);
	*tag = ERROR;
}

int			ft_tagindex(char *param_arg, int *tag)
{
	int		i;

	i = -1;
	while (param_arg[++i])
	{
		if (param_arg[i] == '#' && (*tag = END_HASH))
		{
			if (i == 0)
				*tag = START_HASH;
			else if (param_arg[i + 1] == '#')
				*tag = TWO_HASH;
		}
		if (param_arg[i] == '%' && (*tag = MODULO) && i == 0)
		{
			ft_badsubstitution(param_arg, tag);
			return (-2);
		}
		if (param_arg[i] == '%' && param_arg[i + 1] == '%')
			*tag = TWO_MODULO;
		if (*tag)
			return (i);
		if (param_arg[i] == ':')
			return (ft_specifytags(i, param_arg, tag));
	}
	return (-1);
}

int			ft_badsubstitutiondetector(char *param, int *tag)
{
	int		i;

	i = 0;
	while (param[i])
	{
		if (i == 0 && !ft_isalpha(param[i]) && param[i] != '_')
		{
			ft_badsubstitution(param, tag);
			return (-2);
		}
		if (i > 0 && !(ft_isalnum(param[i])) && param[i] != '_')
		{
			ft_badsubstitution(param, tag);
			return (-2);
		}
		i++;
	}
	return (0);
}

void		ft_normalvalue(char **param_arg, int *tag)
{
	char	*value;

	if (*tag == NONE)
	{
		if (ft_strequ(*param_arg, "?"))
		{
			value = ft_getintern("status");
			ft_strdel(param_arg);
			if (value)
				*param_arg = ft_strdup(value);
			return ;
		}
		ft_badsubstitutiondetector(*param_arg, tag);
		if (*tag != ERROR)
		{
			value = ft_getintern(*param_arg);
			ft_strdel(param_arg);
			if (value)
				*param_arg = ft_strdup(value);
		}
	}
}
