/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 21:22:57 by hessabra          #+#    #+#             */
/*   Updated: 2019/10/10 20:40:26 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrv(char *dest, const char *src)
{
	int		i;
	int		j;
	char	*tmp;

	j = ft_strlen(dest);
	tmp = ft_strsub(src, 0, j);
	i = ft_strlen(tmp);
	while (i != -1)
	{
		dest[j] = tmp[i];
		i--;
		j--;
	}
	ft_strdel(&tmp);
	return (dest);
}

static char	*ft_strcp(char *dest, const char *src)
{
	int		i;
	int		j;

	i = 0;
	if (ft_strlen(src) <= ft_strlen(dest))
		j = ft_strlen(src);
	else
		j = ft_strlen(dest);
	while (i < j)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

static void	ft_racc(char **new, t_need a, char *c)
{
	*new = ft_memset(*new, ' ', a.width);
	(*new)[a.width] = '\0';
	if ((a.flag)[4] == 8)
		*new = ft_strcp(*new, c);
	else
		*new = ft_strrv(*new, c);
}

static int	ft_racc1(t_need *a, int i, char **new)
{
	if (a->precision == -2 || a->precision > i)
	{
		(i > a->width) ? (a->width = i) : i;
		*new = (char *)ft_mema(sizeof(char) * (a->width + 1));
		return (0);
	}
	return (1);
}

char		*ft_cases(t_need a, va_list ap)
{
	char	*new;
	int		i;
	char	*c;

	if (a.width == -1)
		a.width = va_arg(ap, int);
	if (a.precision == -1)
		a.precision = va_arg(ap, int);
	c = va_arg(ap, char *);
	if (c == NULL)
		c = "(null)";
	i = ft_strlen(c);
	if (ft_racc1(&a, i, &new))
	{
		new = c;
		c = ft_strsub(c, 0, a.precision);
		(a.width < a.precision) ? a.width = a.precision : a.width;
		new = (char *)ft_mema(sizeof(char) * (a.width + 1));
		i = -1;
	}
	ft_racc(&new, a, c);
	if (i == -1)
		free(c);
	return (new);
}
