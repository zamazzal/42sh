/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:24:39 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/20 06:50:29 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_makevar(char *key, char *value)
{
	char *var;

	if (!key)
		return (NULL);
	var = ft_strjoin(key, "=");
	var = ft_strjoin_lite(var, value);
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
