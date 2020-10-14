/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 01:31:43 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/16 03:32:20 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_lenparam(char *line, int *i)
{
	int		len;

	len = 0;
	while (line[*i] && line[*i] != '}')
	{
		(*i)++;
		len++;
	}
	if (line[*i] == '}')
	{
		(*i)++;
		len++;
	}
	return (len);
}

int			nextisvar(char *var, char c)
{
	char	*test;
	int		rtn;

	rtn = 0;
	if (!var)
		return (0);
	test = ft_strdup(var);
	ft_strappend(&test, c, TRUE);
	if (ft_strequ(test, "?"))
	{
		rtn = ft_getintern("status") ? 1 : 0;
	}
	else if (ft_getintern(test))
		rtn = 1;
	else
		rtn = 0;
	ft_strdel(&test);
	return (rtn);
}

int			ft_expand(char *line, int *i, char **result)
{
	int		start;
	int		end;
	int		returnval;
	char	*tmp;

	start = *i;
	tmp = NULL;
	end = ft_lenparam(line, i);
	tmp = ft_strsub(line, start, end);
	returnval = ft_parameters(&tmp);
	if (returnval == -2 || returnval == -1 || !tmp)
	{
		ft_strdel(&tmp);
		return (returnval);
	}
	*result = ft_jandf(*result, tmp, 1, 1);
	return (returnval);
}
