/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:57:34 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/03 13:14:06 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/alias_unalias.h"
#include <stdio.h>

void			ft_zaapquote(char *line, int *i, int *len)
{
	char		c;
	
	c = line[*i];
	(*i)++;
	(*len)++;
	while (line[*i] && line[*i] != c)
	{
		(*i)++;
		(*len)++;
	}
	if (line[*i])
	{
		(*i)++;
		(*len)++;
	}
}

int				ft_lencmd(char *line, int *i, int *j)
{
	int			len;

	if (line[*i] == '>' || line[*i] == '<' || line[*i] == '&' || line[*i] == '|' || line[*i] == ';')
		(*i)++;
	len = 0;
	while (line[*i] && line[*i] < 33)
		(*i)++;
	*j = *i;
	while (line[*i] > 32 && line[*i] != '>' && line[*i] != '<' &&
			line[*i] != '&' && line[*i] != '|' && line[*i] != ';')
	{

		if (line[*i] == 39 || line[*i] == 34)
			ft_zaapquote(line, i, &len);
		else
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

int				ft_lenarg(char *line, int *i, int *j)
{
	int			len;

	len = 0;
	while (line[*i] && line[*i] < 33)
		(*i)++;
	*j = *i;
	while (line[*i] && line[*i] != '|' && line[*i] != ';' &&
		(line[*i] != '&' || (line[*i] == '&' && (line[*i + 1] == '>' ||
		line[*i + 1] == '<' || line[*i - 1] == '>' || line[*i - 1] == '<'))))
	{
		if (line[*i] == 39 || line[*i] == 34)
			ft_zaapquote(line, i, &len);
		else
		{
			(*i)++;
			len++;
		}
	}
	if (line[*i] && !line[*i + 1])
		(*i)++;
	if (line[*i])
		len++;
	return (len);
}

char			**ft_getcmds(char *line, int *isodd)
{
	char		**cmds;
	char		*tmp;
	int			j;
	int			i;
	int			len;
	int			tablen;

	line = ft_strtrim(line);

	cmds = (char **)ft_memalloc(sizeof(char *));
	cmds[0] = 0;

	*isodd = 0;
	if (line[0] == '&' || line[0] == '|' || line[0] == ';' || line[0] == '>' || line[0] == '<')
		*isodd = 1;

	i = 0;
	tablen = 0;

	while (line[i])
	{
		printf("\nline[%d] == %c tablen == %d  isod == %d\n", i, line[i], tablen, *isodd);
		if (tablen % 2 == *isodd)
		{
			len = ft_lencmd(line, &i, &j);
			tmp = ft_strsub(line, j, len);
			printf("\ncmd === %s \n", tmp);
			cmds = ft_addtotab(cmds, tmp);
			ft_strdel(&tmp);
		}
		else
		{
			len = ft_lenarg(line, &i, &j);
			printf("\n LEN == %d\n", len);
			tmp = ft_strsub(line, j, len);
			printf("\n rest=== %s \n", tmp);
			cmds = ft_addtotab(cmds, tmp);
			ft_strdel(&tmp);
		}
		tablen++;
	}
	return (cmds);
}

void			ft_replacealiass(char **line, char **allaliases)
{
	int			i;
	int			isodd;
	char		**loopdetector;
	char		**cmds;

	cmds = ft_getcmds(*line, &isodd);
	ft_strdel(line);
	loopdetector = (char **)malloc(sizeof(char *));
	loopdetector[0] = 0;
	i = 0;
	while (cmds[i])
	{
		if (i % 2 == isodd)
			cmds[i] = ft_getaliasvalue(cmds[i], allaliases, loopdetector);
		i++;
	}
	dfre(loopdetector);
	*line = ft_tabtostr(cmds);
}