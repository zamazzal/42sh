/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_expansion1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:16:27 by helmanso          #+#    #+#             */
/*   Updated: 2020/01/21 12:16:59 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_join(char *dest, char *src, int *j)
{
	int	i;
	int	len;

	i = 0;
	len = *j;
	while (src[i] != '\0')
	{
		dest[len] = src[i];
		i++;
		len++;
		(*j)++;
	}
	return (dest);
}

int		ft_nbrlen(char *str, int i)
{
	int	j;

	j = 0;
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		j++;
		i++;
	}
	return (j);
}

int		expansion_num(char *str, int i)
{
	int num;
	int j;

	j = 0;
	num = 0;
	if (ft_nbrlen(str, i) >= 9)
		return (900);
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int		ft_strstr1(char *dest, char *src)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while ((dest[i] != '\0' && src[i] != '\0') && (src[i] == dest[i]))
	{
		j++;
		i++;
		if (src[i] != dest[i] && (src[i] != ' ' && src[i]))
			return (0);
	}
	return (j);
}

int		expansion_word(int i, char *line)
{
	int	j;

	j = g_readline->indexfor_history - 1;
	while (j >= 0)
	{
		if (ft_strstr1(g_readline->history[j], &line[i]))
			return (j);
		j--;
	}
	return (-55);
}
