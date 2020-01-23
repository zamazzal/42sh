/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 00:22:10 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/18 00:49:00 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new;
	t_list		*l;
	t_list		*l_n;

	if (lst == NULL || f == NULL)
		return (NULL);
	l = lst;
	l_n = f(l);
	new = l_n;
	l = l->next;
	while (l != NULL)
	{
		new->next = f(l);
		new = new->next;
		l = l->next;
	}
	return (l_n);
}
