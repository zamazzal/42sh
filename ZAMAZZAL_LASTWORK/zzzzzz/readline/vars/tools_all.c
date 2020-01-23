/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:27:48 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/20 06:50:40 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				checkbackslash(char *ptr, int i)
{
	int c;

	i--;
	c = 0;
	while (i >= 0)
	{
		if (ptr[i] == '\\')
			c++;
		if (ptr[i] != '\\')
			break ;
		i--;
	}
	return (c);
}

int		ft_strinstr(const char *s1, const char *s2, int len)
{
	int i;
	int j;

	if (!s1)
		return (0);
	if (s2[0] == '\0')
		return (1);
	i = 0;
	while ((s1[i] != '\0') && (i < len))
	{
		j = 0;
		while (s2[j] != '\0')
		{
			if (s1[i + j] != s2[j] || j + i >= len)
				break ;
			j++;
		}
		if (s2[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		ft_checkcinstr(char *ptr, int c)
{
	int i;

	i = 0;
	while (ptr[i] != '\0')
	{
		if (ptr[i] == '\"')
		{
			i++;
			while (ptr[i] && ptr[i] != '\"')
				i++;
		}
		if (ptr[i] == '\'')
		{
			i++;
			while (ptr[i] && ptr[i] != '\'')
				i++;
		}
		if (ptr[i] == c && !(checkbackslash(ptr, i) % 2))
			return (1);
		i++;
	}
	return (0);
}

void	ft_puttables(char **table)
{
	size_t	i;

	i = 0;
	while (table[i] != NULL)
		ft_putendl(table[i++]);
}

char	*ft_strjoin_lite(char *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	if (!(ptr = (char*)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	ft_strcpy(ptr, s1);
	ft_strcat(ptr, s2);
	if (s1)
		ft_strdel(&s1);
	return (ptr);
}

char	*ft_strsub_lite(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s || len <= 0 || (int)start < 0)
		return (NULL);
	if (!(ptr = (char*)malloc(len + 1)))
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

char		**ft_addtotab_var(char **tabl, char *str)
{
	int		i;
	int		len;
	char	**new;

	i = 0;
	len = ft_tablen(tabl) + 1;
	SAFE(new = (char **)malloc(sizeof(char*) * (len + 1)));
	while (tabl[i] != NULL)
	{
		new[i] = tabl[i];
		i++;
	}
	new[i] = ft_strdup(str);
	new[++i] = NULL;
	free(tabl);
	return (new);
}

char	**ft_tabdup(char **array)
{
	int		i;
	char	**new;

	i = 0;
	SAFE(new = (char **)malloc(sizeof(char *) * (ft_tablen(array) + 1)));
	while (array[i] != NULL)
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_freetable(char ***array)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_tablen(*array);
	while (i < size)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	(*array) = NULL;
}

char			**ft_jointab(char **tab1, char **tab2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	**new;

	i = 0;
	j = 0;
	len1 = ft_tablen(tab1);
	len2 = ft_tablen(tab2);
	SAFE(new = (char **)malloc(sizeof(char*) * (len1 + len2 + 1)));
	while (tab1[i] != NULL)
		new[j++] = ft_strdup(tab1[i++]);
	i = 0;
	while (tab2[i] != NULL)
		new[j++] = ft_strdup(tab2[i++]);
	new[j] = NULL;
	ft_freetable(&tab1);
	return (new);
}
