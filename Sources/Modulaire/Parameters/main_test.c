/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:58:24 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/16 22:11:18 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/shell.h"
#include <stdio.h>

int     main(int gc, char **gv)
{
    char    **all_params;
    char    *param_arg;

    if (gc > 0)
    {
        all_params = (char **)ft_mmalloc(sizeof(char *) * 5);
        all_params[0] = ft_strdup("a=b");
        all_params[1] = ft_strdup("h=testtesttest");
        all_params[2] = ft_strdup("d=hello");
        all_params[3] = ft_strdup("c=");
        all_params[4] = 0;

        param_arg = ft_strdup(gv[1]);
        printf("\nparam_arg%s\n gv == %s\n", param_arg, gv[1]);
        ft_parameters(&param_arg, &all_params);
        printf("\n|-- %s --|\n", param_arg);
		printf("c == |-- %s --|\n", all_params[3]);
        dfre(all_params);
    }
    return (0);
}
