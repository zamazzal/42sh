/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_s1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 16:24:50 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 03:16:46 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*ft_strstp(char *str, int i)
{
	char	*ptr;
	int		j;

	j = 0;
	ptr = ft_strnew(i);
	while (str[i] != '\0' && j < i)
	{
		ptr[j] = str[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

static	int	ft_strdoublefree(char **line, char **new)
{
	ft_strdel(line);
	ft_strdel(new);
	return (0);
}

int			ft_check_eq(char *str)
{
	int		i;
	int		hist;
	char	*line;
	char	*new;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			new = ft_strstp(str, i);
			if ((hist = get_hist_num(new)) >= 0)
			{
				line = ft_replace(
				g_readline->history[hist], new, &str[i + 1]);
				ft_strdel(&g_readline->editor);
				g_readline->editor = ft_strdup(line);
				ft_strdoublefree(&line, &new);
				return (1);
			}
			ft_strdel(&new);
		}
		i++;
	}
	return (0);
}

int			ft_check_src(char *line, char *src, int i)
{
	int j;

	j = 0;
	if (ft_strlen(line) - i < ft_strlen(src))
		return (0);
	while (line[i + j] != '\0' && src[j])
	{
		if (line[i + j] != src[j])
			return (0);
		j++;
	}
	return (1);
}

char		*ft_replace(char *line, char *src, char *to_rep)
{
	char	*tmp;
	int		i;
	char	*line_new;

	i = 0;
	line_new = ft_strdup(line);
	while (line_new[i] != '\0')
	{
		if (ft_check_src(line_new, src, i))
		{
			tmp = line_new;
			line_new = ft_remplacer_str(line_new, src, to_rep);
			ft_strdel(&tmp);
			i = 0;
		}
		else
			i++;
	}
	return (line_new);
}
