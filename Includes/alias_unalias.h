/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_unalias.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:21:54 by hessabra          #+#    #+#             */
/*   Updated: 2020/02/03 13:01:47 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_UNALIAS_H
# define ALIAS_UNALIAS_H

# include "../Libft/libft.h"

int			ft_lentoequal(char *alias_arg);

char		*ft_addquote(char *arg);
void		ft_putaliases(char **all_aliases, int index);
int			ft_aliasexist(char *alias, char **all_aliases);
int			ft_aliasoption(char *arg);
void		ft_addalias(char *alias_arg, char ***all_aliases);

int			ft_unaliasoption(char *arg);
char		*ft_getaliasvalue(char *arg, char **all_aliases,
									char **loopdetector);

#endif
