/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantions_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:12:15 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 22:16:54 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*ft_strojoin(char **s1, char *s2, int overwrite)
{
	char	*tmp;

	if (overwrite)
	{
		tmp = ft_strjoin(*s1, s2);
		ft_strdel(s1);
		(*s1) = tmp;
		return (NULL);
	}
	return (ft_strjoin(*s1, s2));
}

int			ft_tablen(char **array)
{
	int	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len] != NULL)
		len++;
	return (len);
}

int			ft_skipspaces(char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

void		ft_putintab(char ***a_chain, char *entry)
{
	char	**new;
	size_t	size;
	size_t	i;

	size = ft_tablen(*a_chain);
	if (!(new = (char **)ft_mmalloc(sizeof(char *) * (size + 2))))
		return ;
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup((*a_chain)[i]);
		i++;
	}
	new[i] = ft_strdup(entry);
	i++;
	new[i] = NULL;
	ft_freetable(a_chain);
	*a_chain = new;
}

char		*ft_strappend(char **a_s1, char c, int overwrite)
{
	char	*new;
	int		i;

	SAFE(new = (char *)ft_mmalloc(sizeof(char) * (ft_strlen(*a_s1) + 2)));
	i = 0;
	while (*a_s1 && (*a_s1)[i])
	{
		new[i] = (*a_s1)[i];
		i++;
	}
	new[i] = c;
	new[++i] = '\0';
	if (overwrite == 1)
	{
		ft_strdel(a_s1);
		*a_s1 = new;
		return (NULL);
	}
	return (new);
}
