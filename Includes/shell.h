/* ************************************************************************************************ */
/*                                                                                                  */
/*                                                        :::   ::::::::   ::::::::  :::::::::::    */
/*   shell.h                                           :+:+:  :+:    :+: :+:    :+: :+:     :+:     */
/*                                                      +:+         +:+        +:+        +:+       */
/*   By: sopu <sopu@student.1337.ma>                   +#+      +#++:      +#++:        +#+         */
/*                                                    +#+         +#+        +#+      +#+           */
/*   Created: Invalid date        by                 #+#  #+#    #+# #+#    #+#     #+#             */
/*   Updated: 2020/02/02 14:46:26 by sopu         ####### ########   ########      ###.ma           */
/*                                                                                                  */
/* ************************************************************************************************ */

#ifndef SHELL_H
# define SHELL_H

# include "../Libft/libft.h"

int			alias(char **arg, char ***all_aliases);
int			unalias(char **arg, char ***all_aliases);
int			ft_parameters(char **param_arg, char ***all_params);
void		ft_replacealiass(char **line, char **allaliases);

#endif
