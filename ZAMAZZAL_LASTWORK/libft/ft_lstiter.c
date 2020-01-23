/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 00:16:25 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/18 00:21:59 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*l;

	if (lst == NULL || f == NULL)
		return ;
	l = lst;
	while (l != NULL)
	{
		f(l);
		l = l->next;
	}
}
