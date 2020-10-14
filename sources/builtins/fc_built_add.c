/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_built_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 21:53:37 by helmanso          #+#    #+#             */
/*   Updated: 2020/02/16 00:47:15 by helmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char	*ft_return_flag(char *arg)
{
	char	*newarg;
	char	*ptr;
	char	c[2];
	int		i;

	i = 0;
	newarg = NULL;
	c[1] = '\0';
	while (arg[i])
	{
		c[0] = arg[i];
		argument_join(&newarg, "-");
		ptr = newarg;
		newarg = ft_strjoin(newarg, c);
		free(ptr);
		i++;
	}
	return (newarg);
}

char	**ft_check_all(char **arg)
{
	char	**new;
	int		i;
	char	**tmp;
	char	*flag;

	new = (char **)ft_mmalloc(sizeof(char *) * 100);
	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '-' && (!ft_isdigit(arg[i][1])
		&& !ft_isdigit(arg[i][2])))
		{
			flag = ft_return_flag(arg[i] + 1);
			tmp = ft_strsplit(flag, ' ');
			ft_strdel(&flag);
			if (tmp)
				new = ft_jointab(new, tmp);
			ft_freetable(&tmp);
		}
		else
			new = ft_addtotab(new, arg[i]);
		i++;
	}
	return (new);
}

int		ft_check_editor(char *arg)
{
	if (ft_strcmp(arg, "vim") && ft_strcmp(arg, "emacs") &&
	ft_strcmp(arg, "nano") && ft_strcmp(arg, "cat"))
		return (0);
	return (1);
}

void	ft_initialize_fc(void)
{
	g_readline->e = 0;
	g_readline->n = 0;
	g_readline->r = 0;
	g_readline->num1 = 0;
	g_readline->num2 = 0;
	g_readline->l = 0;
	g_readline->editor = NULL;
}
