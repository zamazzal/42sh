/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 02:13:58 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/12 04:43:07 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		type_of_argument(const char *arg, size_t i)
{
	if ((!i || arg[i - 1] != '\\') && arg[i] == '|' && arg[i + 1] != '|')
		return (PIPE);
	else if (((!i || arg[i - 1] != '\\') && arg[i] == '&' && arg[i + 1] == '&')
	&& (!i || ((arg[i - 1] != '<' && arg[i - 1] != '>'))
	|| ((i - 1) && (arg[i - 2] == '&'))))
		return (AND);
	else if (((!i || arg[i - 1] != '\\') && arg[i] == '&')
	&& (((!i || (arg[i - 1] != '<' && arg[i - 1] != '>'))
	&& (arg[i + 1] != '<' && arg[i + 1] != '>'))
		|| ((i - 1) && arg[i - 2] == '&')))
		return (BG);
	else if ((!i || arg[i - 1] != '\\') && arg[i] == '|' && arg[i + 1] == '|')
		return (OUR);
	else if ((!i || arg[i - 1] != '\\') && arg[i] == ';')
		return (SEP);
	return (0);
}

int		is_near(ushort type)
{
	ft_putstr_fd("42sh: parse error near ", 2);
	if (type == PIPE)
		ft_putendl_fd("`|'", 2);
	else if (type == AND)
		ft_putendl_fd("`&&'", 2);
	else if (type == OUR)
		ft_putendl_fd("`||'", 2);
	else if (type == SEP)
		ft_putendl_fd("`;;'", 2);
	else if (type == BG)
		ft_putendl_fd("`&'", 2);
	else if (type)
		ft_putendl_fd((char*)&type, 2);
	else
		ft_putendl_fd("`\\n'", 2);
	return (-1);
}

int		redirec_isnear(ushort type)
{
	ft_putstr_fd("42sh: parse error near ", 2);
	if (type == APPEN_TF)
		ft_putendl_fd("`>>'", 2);
	else if (type == TRUNC_TF)
		ft_putendl_fd("`>'", 2);
	else if (type == HERE_STRING)
		ft_putendl_fd("`<<<'", 2);
	else if (type == READ_FILE)
		ft_putendl_fd("`<'", 2);
	else if (type == HERE_DOC)
		ft_putendl_fd("`<<'", 2);
	else if (type == READ_FCUSFD)
		ft_putendl_fd("`<&'", 2);
	else if (type == SWAP_LFD_TRFD)
		ft_putendl_fd("`>&'", 2);
	else
		ft_putendl_fd("`\\n'", 2);
	return (-1);
}
