/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:09:32 by kbahrar           #+#    #+#             */
/*   Updated: 2020/02/12 19:03:19 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_putescape(char c)
{
	if (c == 'n')
		ft_putchar('\n');
	else if (c == 'a')
		ft_putchar('\a');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'e' || c == 'E')
		ft_putchar('\e');
	else if (c == 'f')
		ft_putchar('\f');
	else if (c == 'r')
		ft_putchar('\r');
	else if (c == 't')
		ft_putchar('\t');
	else if (c == 'v')
		ft_putchar('\v');
	else if (c == '\\')
		ft_putchar('\\');
	else if (c == '0')
		ft_putchar('\0');
	else
		return (0);
	return (1);
}

static void	ft_putstr_echo(char *str, int *opt)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && (opt[2] == -1 || opt[1] == 1))
		{
			if (ft_putescape(str[i + 1]) == 1)
				i++;
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
}

static int	get_options(int *opt, char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'n')
			opt[0] = 1;
		else if (str[i] == 'e')
			opt[1] = 1;
		else if (str[i] == 'E')
			opt[2] = 1;
		else
		{
			i = 0;
			while (i < 3)
				opt[i++] = -1;
			return (-1);
		}
		i++;
	}
	return (0);
}

static void	make_options(int *opt, int *place, char **args)
{
	int		i;
	int		flag;

	i = 0;
	while (i < 3)
		opt[i++] = -1;
	i = 1;
	flag = 0;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1])
			flag = get_options(opt, args[i]);
		else
			flag = -1;
		if (flag == -1)
			return ;
		i++;
		*place = i;
	}
}

int			ft_echo(char **args)
{
	int	opt[3];
	int	i;

	i = 1;
	errno = 0;
	if (write(1, "", 0) == -1)
	{
		ft_perror("42sh: echo");
		return (1);
	}
	if (!args[i])
	{
		ft_putchar('\n');
		return (0);
	}
	make_options(opt, &i, args);
	while (args[i])
	{
		ft_putstr_echo(args[i], opt);
		i++;
		(args[i]) ? ft_putchar(' ') : 0;
	}
	if (opt[0] == -1)
		ft_putchar('\n');
	return (0);
}
