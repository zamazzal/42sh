/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:24:22 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/20 06:50:24 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char			*ft_getintern(const char *name)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	if (!name)
		return (NULL);
	env = ft_strjoin(name, "=");
	len = ft_strlen(env);
	while (g_intern[i] != NULL)
	{
		if (ft_strinstr(g_intern[i], env, len))
		{
			ft_strdel(&env);
			return (ft_strchr(g_intern[i], '=') + 1);
		}
		i++;
	}
	ft_strdel(&env);
	return (NULL);
}

char			*ft_getenv(const char *name)
{
	int		i;
	int		len;
	char	*env;

	i = 0;
	if (!name)
		return (NULL);
	env = ft_strjoin(name, "=");
	len = ft_strlen(env);
	while (g_environ[i] != NULL)
	{
		if (ft_strinstr(g_environ[i], env, len))
		{
			ft_strdel(&env);
			return (ft_strchr(g_environ[i], '=') + 1);
		}
		i++;
	}
	ft_strdel(&env);
	return (NULL);
}
