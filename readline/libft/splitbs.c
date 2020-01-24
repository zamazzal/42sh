/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitbs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 13:56:11 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/08 05:29:58 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int		ft_count(char *str, int *bs)
{
	int			i;
	int			nb;
	int			flag;
	int			mark;

	i = 0;
	nb = 0;
	flag = 0;
	while (str[i] && (mark = 1))
	{
		if (str[i] == 92)
		{
			(*bs > 0) ? mark = 0 : mark;
			i += ft_entier(*bs);
			bs++;
		}
		(ft_is_whitespace(str[i]) && mark && flag == 1) ? flag = 0 : flag;
		if (!ft_is_whitespace(str[i]) && flag == 0)
		{
			nb++;
			flag = 1;
		}
		i++;
	}
	return (nb);
}

static int		ft_size(char *str, int p, int **bs)
{
	int			i;
	int			mark;

	i = p;
	while (str[i] && (!ft_is_whitespace(str[i]) || !mark))
	{
		mark = 1;
		if (str[i] == 92)
		{
			(**bs > 0) ? mark = 0 : mark;
			i += ft_entier(**bs);
			(*bs)++;
		}
		else
			i++;
	}
	return (i - p);
}

static void		ft_pos(char *str, int *p)
{
	while (str[*p])
	{
		if (!ft_is_whitespace(str[*p]))
			return ;
		(*p)++;
	}
}

char			**ft_splitbs(char *str, int *bs)
{
	t_splitbs	ij;
	int			len;
	int			lenarg;
	int			p[1];
	char		**tab_str;

	ij.i = 0;
	*p = 0;
	lenarg = ft_count(str, bs);
	tab_str = (char**)ft_mema(sizeof(char*) * (lenarg + 1));
	if (tab_str)
	{
		while (ij.i < lenarg && !(ij.j = 0))
		{
			ft_pos(str, p);
			len = ft_size(str, *p, &bs);
			tab_str[ij.i] = (char*)ft_mema(sizeof(char) * (len + 1));
			while (ij.j < len)
				tab_str[ij.i][(ij.j)++] = str[(*p)++];
			tab_str[ij.i][ij.j] = '\0';
			(ij.i)++;
		}
		tab_str[lenarg] = 0;
	}
	return (tab_str);
}
