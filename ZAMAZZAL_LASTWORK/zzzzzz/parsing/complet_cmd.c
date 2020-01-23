/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:48:58 by oboualla          #+#    #+#             */
/*   Updated: 2019/12/29 15:52:39 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/parsing.h"

void    complet_type(char **cmd, t_ushort dernier_type)
{
    char *prompt;
    char *complet;

    complet = NULL;
    if (dernier_type == PIPE)
        prompt = "pipe> ";
    else if (dernier_type == AND)
        prompt = "cmdand> ";
    else if (dernier_type == OUR)
        prompt = "cmdor> ";
    complet = readline(prompt);
    argument_join(cmd, complet);
    free(complet);
}
