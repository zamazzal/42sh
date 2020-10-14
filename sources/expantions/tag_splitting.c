/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_splitting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 23:24:41 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/16 03:35:33 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char	*ft_tagvalue(int tag)
{
	if (tag == INTEROGATION)
		return (ft_strdup(":?"));
	if (tag == PLUS)
		return (ft_strdup(":+"));
	if (tag == MINCE)
		return (ft_strdup(":-"));
	if (tag == EQUAL)
		return (ft_strdup(":="));
	if (tag == TWO_HASH)
		return (ft_strdup("##"));
	if (tag == END_HASH)
		return (ft_strdup("#"));
	if (tag == MODULO)
		return (ft_strdup("%"));
	if (tag == TWO_MODULO)
		return (ft_strdup("%%"));
	return (NULL);
}

char		**ft_splittotwo(char *param_arg, int tag)
{
	char	*tag_value;
	char	*va;
	char	**splited;

	tag_value = ft_tagvalue(tag);
	va = ft_strstr(param_arg, tag_value);
	splited = (char **)ft_mmalloc(sizeof(char *) * 3);
	splited[1] = ft_strdup(va + ft_strlen(tag_value));
	splited[0] = ft_strsub(param_arg, 0, ft_strlen(param_arg) - ft_strlen(va));
	splited[2] = 0;
	ft_strdel(&tag_value);
	return (splited);
}
