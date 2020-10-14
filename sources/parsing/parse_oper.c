/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:14:03 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/12 02:53:53 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			change_to_opor(t_parse **parse, t_parse *lst)
{
	if (!(*parse)->cmd)
	{
		is_near(OUR);
		return (-1);
	}
	*parse = lst;
	point_final_node(parse);
	if (!((*parse)->if_fail = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (-1);
	(*parse) = (*parse)->if_fail;
	return (1);
}

int			change_to_seperat(t_parse **parse, t_parse *lst)
{
	if (!(*parse)->cmd)
		return (1);
	if (lst->next)
		change_to_seperat(parse, lst->next);
	else
	{
		*parse = lst;
		if (!((*parse)->next = (t_parse*)ft_memalloc(sizeof(t_parse))))
			return (-1);
		*parse = (*parse)->next;
	}
	return (1);
}

int			change_to_opand(t_parse **parse, t_parse *lst)
{
	if (!(*parse)->cmd)
	{
		is_near(AND);
		return (-1);
	}
	*parse = lst;
	if (!(point_final_node(parse)))
		return (-1);
	if (!((*parse)->if_seccess = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (-1);
	(*parse) = (*parse)->if_seccess;
	return (1);
}

int			is_background(t_parse **parse, t_parse *lst)
{
	if (!(*parse)->cmd)
		return (is_near(BG));
	if (lst->next)
		is_background(parse, lst->next);
	else
	{
		while (lst->next)
			lst = lst->next;
		*parse = lst;
		(*parse)->bg = 1;
		change_to_seperat(parse, lst);
	}
	return (1);
}
