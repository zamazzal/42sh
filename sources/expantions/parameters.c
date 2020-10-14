/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:53:29 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/16 03:35:13 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		*ft_takeofbraces(char *arg)
{
	int		i;
	int		j;
	int		len_new_arg;
	char	*new_arg;

	len_new_arg = ft_strlen(arg) - 3;
	new_arg = (char *)ft_mmalloc(sizeof(char) * (len_new_arg + 1));
	i = 0;
	j = 2;
	while (i < len_new_arg)
	{
		new_arg[i] = arg[j];
		i++;
		j++;
	}
	ft_strdel(&arg);
	return (new_arg);
}

static int		ft_returnvalue(int tag, char *param_arg)
{
	if (tag == ERROR_STOP)
		return (-2);
	if (tag == ERROR)
		return (-1);
	if (param_arg == NULL)
		return (1);
	return (0);
}

int				ft_parameters(char **param_arg)
{
	char		**splited;
	int			tag;

	*param_arg = ft_takeofbraces(*param_arg);
	tag = NONE;
	ft_tagindex(*param_arg, &tag);
	if (tag != ERROR)
	{
		if (tag != NONE && tag != START_HASH)
		{
			splited = ft_splittotwo(*param_arg, tag);
			ft_badsubstitutiondetector(splited[0], &tag);
			if (tag != ERROR)
				ft_splitytags(splited, &tag, param_arg);
			dfre(splited);
		}
		if (tag == START_HASH)
			ft_starthash(param_arg, &tag);
		ft_normalvalue(param_arg, &tag);
	}
	return (ft_returnvalue(tag, *param_arg));
}
