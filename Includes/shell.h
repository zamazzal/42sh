/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:35:21 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/20 05:49:09 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../Libft/libft.h"

int			alias(char **arg, char ***all_aliases);
int			unalias(char **arg, char ***all_aliases);
int			ft_parameters(char **param_arg, char ***all_params);
char		*ft_getaliasvalue(char *arg, char **all_aliases,
									char **loopdetector);

#endif
