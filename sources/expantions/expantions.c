/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:29:44 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/16 03:33:15 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ms_set_quote(int *quoted, char *quote, char c)
{
	if (c == '\'' && (*quoted) == FALSE)
	{
		(*quoted) = TRUE;
		(*quote) = c;
	}
	else if (c == '\'' && (*quoted) == TRUE && (*quote) == '\'')
	{
		(*quoted) = FALSE;
		(*quote) = 0;
	}
	else if (c == '\"' && (*quoted) == FALSE)
	{
		(*quoted) = TRUE;
		(*quote) = c;
	}
	else if (c == '\"' && (*quoted) == TRUE && (*quote) == '\"')
	{
		(*quoted) = FALSE;
		(*quote) = 0;
	}
}

char		*ms_expand_quotes(char *arg)
{
	int		i;
	int		quoted;
	char	quote;
	char	*result;

	result = ft_strnew(0);
	quoted = FALSE;
	quote = 0;
	i = 0;
	while (arg[i])
	{
		ms_set_quote(&quoted, &quote, arg[i]);
		if (quoted == FALSE && ft_strchr("\'\"", arg[i]))
			i++;
		else if (arg[i] != quote)
			ft_strappend(&result, arg[i++], TRUE);
		else
			i++;
	}
	return (result);
}

int			ms_expand_dollar(char **buffer, char *arg)
{
	int		i;
	char	*var_name;
	char	*val;

	var_name = ft_strnew(0);
	i = 0;
	while (arg[i] && ft_strchr(ALN, arg[i]))
	{
		if (ft_getintern(var_name) && !nextisvar(var_name, arg[i]))
			break ;
		ft_strappend(&var_name, arg[i], TRUE);
		i++;
	}
	if (ft_strequ(var_name, "?"))
		val = ft_getintern("status");
	else
		val = ft_getintern(var_name);
	if (val)
		ft_strojoin(buffer, val, TRUE);
	ft_strdel(&var_name);
	return (i);
}

char		*ms_expand_dollars(int *ret, char *arg)
{
	int		i;
	int		quoted;
	char	quote;
	char	*result;

	result = ft_strnew(0);
	quoted = FALSE;
	i = 0;
	*ret = 1;
	while (arg[i])
	{
		ms_set_quote(&quoted, &quote, arg[i]);
		if (arg[i] == '$' && ((quoted && quote == '\"') || !quoted))
		{
			if (arg[i + 1] == '{')
				*ret = ft_expand(arg, &i, &result);
			else if (++i)
				i += ms_expand_dollar(&result, arg + i);
			continue ;
		}
		ft_strappend(&result, arg[i], TRUE);
		i++;
	}
	ft_strdel(&arg);
	return (result);
}

char		*ms_expand_tilde(char *arg)
{
	char	*result;
	char	*value;

	result = ft_strnew(0);
	if (arg[0] == '~')
	{
		if ((value = ft_getintern("HOME")))
			ft_strojoin(&result, value, TRUE);
		ft_strojoin(&result, arg + 1, TRUE);
		return (result);
	}
	ft_strdel(&result);
	result = ft_strdup(arg);
	return (result);
}
