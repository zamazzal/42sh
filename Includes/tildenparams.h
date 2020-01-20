/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tildenparams.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 14:17:01 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/16 22:34:35 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILDENPARAMS_H
# define TILDENPARAMS_H

# define NONE 0
# define MINCE 1
# define PLUS 2
# define INTEROGATION 3
# define EQUAL 4
# define START_HASH 5
# define MODULO 6
# define TWO_MODULO 7
# define END_HASH 8
# define TWO_HASH 9
# define ERROR -1
# define ERROR_STOP -2

# include "../Libft/libft.h"
# include "alias_unalias.h"
# include <stdio.h>

void		ft_badsubstitution(char *param_arg, int *tag);
int			ft_badsubstitutiondetector(char *param, int *tag);
void		ft_normalvalue(char **param_arg, int *tag, char **allparams);
int			ft_tagindex(char *param_arg, int *tag);
int			ft_issetornull(char *variablename, char ***allparams,
							int tag, char **arg);
void		ft_splitytags(char **splitted, int *tag,
								char ***allparams, char **arg);
void		ft_hashmodulus(char **splitted, int *tag, char **arg);
void		ft_starthash(char **arg, char **allparams, int *tag);
char		*ft_getintern(const char *name, char **allparams);
char		**ft_splittotwo(char *param_arg, int tag);

#endif