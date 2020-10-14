/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_aggr_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 23:55:46 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/13 16:16:50 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			check_lfd(char *ptr)
{
	size_t i;

	i = 0;
	if (!ptr || !ptr[0])
		return (0);
	while (ptr[i] && ft_isdigit(ptr[i]))
		i++;
	if (ptr[i] && ft_strcmp(&ptr[i], "-"))
		return (-1);
	return (i);
}

char		**save_last_herdoc(char **last_herdoc, int mode)
{
	static char **addr_last_herdoc = NULL;

	if (last_herdoc)
		addr_last_herdoc = last_herdoc;
	if (!mode)
		addr_last_herdoc = NULL;
	return (addr_last_herdoc);
}

void		read_herdoc(char **her_doc)
{
	char *key;
	char *tmp;
	char *read;

	key = *her_doc;
	*her_doc = NULL;
	if (save_last_herdoc(NULL, 1))
		ft_strdel(save_last_herdoc(NULL, 1));
	g_ctrl_dsig = 1;
	g_line_type = L_HDC;
	while ((read = ft_readline("herdoc> \n")) && (g_ctrl_csig && g_ctrl_dsig))
	{
		ft_putchar('\n');
		if (!ft_strcmp(read, key))
			break ;
		tmp = read;
		read = ft_jandf(read, "\n", 1, 0);
		tmp = *her_doc;
		*her_doc = ft_jandf(*her_doc, read, 1, 1);
	}
	g_ctrl_dsig = 1;
	ft_strdel(&read);
	ft_strdel(&key);
	save_last_herdoc(her_doc, 1);
}

void		join_rest_tocmd(char *arg, size_t start, size_t end)
{
	char	*rest;

	rest = ft_strdup(&arg[end]);
	ft_strclr(&arg[start]);
	ft_strcat(arg, rest);
	ft_strdel(&rest);
}

int			get_right_side(t_utils *utils, size_t *end, char **right_side)
{
	size_t type;

	if (!utils->arg[*end])
	{
		if (!(*right_side = get_next_arg(&utils->cmd, &utils->index_arg)))
			return (is_near(0));
		if ((type = type_of_argument(*right_side, 0)))
			return (is_near(type));
	}
	else
	{
		*right_side = ft_strdup(&utils->arg[*end]);
		(*end) += ft_skip_sep(&utils->arg[*end], "0123456789");
	}
	if (check_lfd(*right_side) == -1)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(*right_side, 2);
		ft_putendl_fd(": ambiguous redirect.", 2);
		return (-1);
	}
	return (1);
}
