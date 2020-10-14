/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:24:39 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/15 18:04:54 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_makevar(char *key, char *value)
{
	char *tmp;
	char *var;

	if (!key)
		return (NULL);
	var = ft_strjoin(key, "=");
	tmp = var;
	var = ft_strjoin(tmp, value);
	ft_strdel(&tmp);
	return (var);
}

char	*ft_getkey(char *str)
{
	int		center;
	char	*key;

	center = ft_getcpos(str, '=');
	key = ft_strsub(str, 0, center);
	return (key);
}

char	*ft_getvalue(char *str)
{
	int		center;
	char	*value;

	center = ft_getcpos(str, '=');
	value = ft_strsub(str, center + 1, ft_strlen(str) - (center + 1));
	return (value);
}
