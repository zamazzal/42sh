/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 22:36:17 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/12 22:37:41 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_strsub_lite(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || len <= 0 || (int)start < 0)
		return (NULL);
	if (!(ptr = (char*)ft_mmalloc(len + 1)))
		return (NULL);
	while (i < len && s[start])
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	if (s)
		ft_strdel(&s);
	return (ptr);
}

int		ft_getcpos(char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	**ft_addtotab_var(char **tabl, char *str)
{
	int		i;
	int		len;
	char	**new;

	i = 0;
	len = ft_tablen(tabl) + 1;
	SAFE(new = (char **)ft_mmalloc(sizeof(char*) * (len + 1)));
	while (tabl[i] != NULL)
	{
		new[i] = ft_strdup(tabl[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	new[++i] = NULL;
	dfre(tabl);
	return (new);
}

char	**ft_tabdup(char **array)
{
	int		i;
	char	**new;

	i = 0;
	SAFE(new = (char **)ft_mmalloc(sizeof(char *) * (ft_tablen(array) + 1)));
	while (array[i] != NULL)
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
