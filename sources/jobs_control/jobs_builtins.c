/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 14:04:05 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 18:41:19 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	inform_p_cmd(t_parse *lst)
{
	if (!lst)
		return ;
	ft_printf("      %d              | %s\n", lst->pid, lst->cmd);
	inform_p_cmd(lst->pipe);
}

static void	print_node(t_jobs *node, int option)
{
	if (!option)
		inform_user(node, 0,
		JOBS_ID | JOBS_CUR | JOBS_MODE | JOBS_ALLCMD | JOBS_BG);
	if ((option & FLAGS_P))
		inform_user(node, 0, JOBS_PGID);
	if ((option & FLAGS_L))
	{
		inform_user(node, 0, JOBS_ID | JOBS_CUR | JOBS_MODE | JOBS_PGID);
		ft_printf("\t   %s\n", node->node_cmd->cmd);
		inform_p_cmd(node->node_cmd->pipe);
	}
	else
		ft_putchar('\n');
}

static int	jobs_cmp(char *arg, t_jobs **jobs, int flag, int option)
{
	if (flag || (ft_atoi(arg) == (*jobs)->proc_id))
	{
		print_node(*jobs, option);
		if (!flag)
		{
			*jobs = g_jobs;
			return (0);
		}
	}
	if (!(*jobs = (*jobs)->next) && !flag)
	{
		ft_putstr_fd("42sh: jobs: no such jobs id ", 2);
		ft_putendl_fd(arg, 2);
		*jobs = g_jobs;
		return (0);
	}
	return (1);
}

int			jobs_builtin(char **argv)
{
	t_jobs		*jobs;
	size_t		i;
	int			option;
	int			flags;

	option = 0;
	flags = 0;
	if ((i = get_option(argv, &option)) == -1)
		return (1);
	if (!g_jobs)
		return (0);
	if (!argv[i])
		flags = 1;
	jobs = g_jobs;
	while (jobs && (flags || argv[i]))
		if (!jobs_cmp(argv[i], &jobs, flags, option))
			i++;
	return (0);
}
