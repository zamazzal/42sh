/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:38:35 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/16 03:26:20 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*ft_addquote(char *arg)
{
	char	*new;
	int		i;
	int		j;

	new = (char *)ft_mmalloc(sizeof(char) * (ft_strlen(arg) + 3));
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (i == j && arg[i - 1] == '=')
		{
			new[j] = 39;
			j++;
		}
		new[j] = arg[i];
		i++;
		j++;
	}
	new[j] = 39;
	new[j + 1] = 0;
	ft_strdel(&arg);
	return (new);
}

char		*ft_delquote(char *value)
{
	char	*new;
	int		i;

	i = 0;
	while (value[i] && value[i - 1] != '=')
		i++;
	new = ft_strsub(value, i + 1, ft_strlen(value) - i - 2);
	return (new);
}

char		*ft_changevalue(char *value, char *alias_value,
								int len_tobereplaced)
{
	char	*newvalue;
	int		i;
	int		j;

	newvalue = (char *)ft_mmalloc(sizeof(char) * (ft_strlen(value) -
					len_tobereplaced + ft_strlen(alias_value) + 1));
	j = 0;
	while (alias_value[j])
	{
		newvalue[j] = alias_value[j];
		j++;
	}
	i = len_tobereplaced;
	while (value[i])
	{
		newvalue[j] = value[i];
		j++;
		i++;
	}
	newvalue[j] = 0;
	ft_strdel(&value);
	return (newvalue);
}

void		ft_cpythevalue(char **tobereplaced, char *value, int start)
{
	int		i;

	i = 0;
	while (i < start)
	{
		(*tobereplaced)[i] = value[i];
		i++;
	}
	(*tobereplaced)[i] = 0;
}

char		*ft_getaliasvalue(char *arg, char **all_aliases,
									char ***loopdetector)
{
	char	*value;
	char	*tmp;
	int		index;

	value = ft_strdup(arg);
	tmp = ft_strjoin(arg, "=");
	if ((index = ft_aliasexist(tmp, all_aliases)) > -1 &&
		!ft_existintab(*loopdetector, arg))
	{
		ft_strdel(&tmp);
		*loopdetector = ft_addtotab(*loopdetector, arg);
		tmp = ft_delquote(all_aliases[index]);
		tmp = ft_getaliasvalue(tmp, all_aliases, loopdetector);
		ft_strdel(&value);
		value = tmp;
	}
	else
		ft_strdel(&tmp);
	ft_strdel(&arg);
	return (value);
}
