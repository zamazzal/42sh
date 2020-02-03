/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   alias_replace.c                                   :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: sopu <sopu@student.1337.ma>                   +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: 2020/01/31 07:53:14 by sopu            #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2020/01/31 07:53:14 by sopu         ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#include "../../../Includes/alias_unalias.h"


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
		else;sd
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

char			*ft_replacealiass(char ***cmds, char **allaliases, int isodd)
{
	int	i;
	char	**loopdetector;
	char	*line;

	loopdetector = (char **)malloc(sizeof(char *));
	loopdetector[0] = 0;
	while (*cmds[i])
	{
		if (i % 2 == isodd)
			*cmds[i] = ft_getaliasvalue(*cmds[i], allaliases, loopdetector);
		i++;
	}
	ft_dfre(loopdetector);
	line = ft_tabtostr(*cmds);
	return (line);
}