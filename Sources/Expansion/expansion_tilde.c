/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:41:04 by hessabra          #+#    #+#             */
/*   Updated: 2020/01/23 06:40:44 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expansion.h"

/**
 * Tildedefault is a value that should be stored from the start
 * as the shell start.
**/

int					ft_tildeprefix(char *cmd)
{
	int				i;

	i = 0;

	while (cmd[i] && cmd[i] > 32 && cmd[i] != '/')
		i++;
	return (i);
}

void				ft_initenvariables(t_envariables *vars, int option)
{
	if (option == 1)
	{
		vars->homevalue = ft_strdup(ft_getenv("HOME"));
		vars->oldpwd = ft_strdup(ft_getenv("OLDPWD"));
		vars->pwd = ft_strdup(ft_getenv("PWD"));
	}
	else
	{
		ft_strdel(vars->homevalue);
		ft_strdel(vars->oldpwd);
		ft_strdel(vars->pwd);
	}
}

int					ft_isnum(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void				ft_tilde(char **cmd, int start,
									char *tildedefault, char **env)
{
	int				end;
	char			*tmp;
	t_envariables	vars;

	
	end = ft_tildeprefix(*cmd + start + 1);
	tmp = ft_strsub(*cmd, start + 1, end + 1);
	ft_initenvariables(&vars, 1);
	if (end == 0 && vars.homevalue)
			ft_changestr(cmd, vars.homevalue, start, 1);
	else if (end == 0 && !(vars.homevalue))
		ft_changestr(cmd, tildedefault, start, 1);
	else if (end == 1 && *cmd + start + 1 == '+' && vars.pwd)
		ft_changestr(cmd, vars.pwd, start, end + 1);
	else if (end == 1 && *cmd + start + 1 == '-' && vars.oldpwd)
		ft_changestr(cmd, vars.oldpwd, start, end + 1);
	else if (ft_isnum(tmp) || ((tmp[0] == '+' || tmp[0] == '-') && ft_isnum(tmp + 1)))
	{
		
	}
		
	ft_initenvariables(&vars, 0);
}
