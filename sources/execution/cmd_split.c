/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 02:32:29 by zamazzal          #+#    #+#             */
/*   Updated: 2020/02/15 03:59:59 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_getcindex(char *ptr, int c)
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
			return (i);
		i++;
	}
	return (-1);
}

static int		ft_nbrofc(char *ptr, int c)
{
	int x;
	int nbr;

	nbr = 1;
	x = 0;
	while ((x = ft_getcindex(ptr, c)) != -1)
	{
		ptr += x + 1;
		if (x == 0)
			continue;
		if (*ptr == '\0')
			break ;
		nbr++;
	}
	return (nbr);
}

static char		**putcontent(char *ptr, int len, int c)
{
	int		i;
	int		x;
	int		chrlen;
	char	**cmds;

	i = 0;
	SAFE(cmds = (char **)ft_mmalloc(sizeof(char *) * (len + 1)));
	while ((x = ft_getcindex(ptr, c)) != -1)
	{
		if (x != 0)
			cmds[i++] = ft_strsub(ptr, 0, x);
		ptr += x + 1;
	}
	chrlen = ft_strlen(ptr);
	if (chrlen > 0)
		cmds[i++] = ft_strsub(ptr, 0, chrlen);
	cmds[i] = NULL;
	return (cmds);
}

char			**ft_cmdsplit(char *ptr, int c)
{
	int len;

	if (!ptr[0])
		return (NULL);
	len = ft_nbrofc(ptr, c);
	return (putcontent(ptr, len, c));
}
