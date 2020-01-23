/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 22:30:44 by hessabra          #+#    #+#             */
/*   Updated: 2018/10/17 23:58:08 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*l;
	t_list		*b;

	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	l = *alst;
	while (l != NULL)
	{
		b = l->next;
		del(l->content, l->content_size);
		free(l);
		l = b;
	}
	*alst = NULL;
}
