/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:57:34 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/16 03:29:20 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

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

	if (line[*i] == '>' || line[*i] == '<' || line[*i] == '&' ||
				line[*i] == '|' || line[*i] == ';')
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
	int			index[2];
	int			len;
	int			tablen;

	line = ft_strtrim(line);
	cmds = (char **)ft_memalloc(sizeof(char *));
	*isodd = 0;
	if (line[0] == '&' || line[0] == '|' || line[0] == ';' ||
				line[0] == '>' || line[0] == '<')
		*isodd = 1;
	index[0] = 0;
	tablen = 0;
	while (line[index[0]])
	{
		len = (tablen % 2 == *isodd) ? ft_lencmd(line, &index[0], &index[1]) :
					ft_lenarg(line, &index[0], &index[1]);
		tmp = ft_strsub(line, index[1], len);
		cmds = ft_addtotab(cmds, tmp);
		ft_strdel(&tmp);
		tablen++;
	}
	return (cmds);
}

void			replace_alias(char **line)
{
	char	**loopdetector;
	char	*arg;
	char	*nwline;
	size_t	index[2];

	nwline = NULL;
	index[0] = 0;
	if (!(index[1] = 0) && (!(*line) || !(*line)[0]))
		return ;
	while ((arg = get_next_arg(line, &index[0])))
	{
		if (!index[1] && !type_of_argument(arg, 0))
		{
			loopdetector = (char **)ft_mmalloc(sizeof(char *));
			arg = ft_getaliasvalue(arg, g_all_aliases, &loopdetector);
			dfre(loopdetector);
		}
		index[1] = (type_of_argument(arg, 0)) ? 0 : 1;
		argument_join(&nwline, arg);
		ft_strdel(&arg);
	}
	ft_strdel(line);
	*line = nwline;
}
