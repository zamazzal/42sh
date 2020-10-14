/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_red_aggr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 05:00:06 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/13 20:21:23 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static size_t	ret_red_type(char *arg, size_t index, char type)
{
	if (ft_skip_sep(&arg[index], &type) > 3)
		return (is_near(type));
	if (ft_strnequ(&arg[index], "<<<", 3))
		return (HERE_STRING);
	if (ft_strnequ(&arg[index], "<<", 2))
		return (HERE_DOC);
	if (ft_strnequ(&arg[index], ">>", 2))
		return (APPEN_TF);
	if (ft_strnequ(&arg[index], "<&", 2))
		return (READ_FCUSFD);
	if (ft_strnequ(&arg[index], "<>", 2))
		return (RDWR_TF);
	if (ft_strnequ(&arg[index], "<", 1))
		return (READ_FILE);
	if (ft_strnequ(&arg[index], ">&", 2))
		return (SWAP_LFD_TRFD);
	if (ft_strnequ(&arg[index], ">", 1))
		return (TRUNC_TF);
	return (0);
}

int				stock_lfd(char *arg, t_redirections *redr, size_t *start)
{
	if (*start && arg[*start - 1] == '&')
	{
		(*start)--;
		redr->red_type |= REDR_STIN_STOUT;
	}
	else if (*start && ft_isdigit(arg[*start - 1]))
	{
		(*start)--;
		while (*start > 0 && ft_isdigit(arg[*start - 1]))
			(*start)--;
		redr->left_fd = ft_atoi(&arg[*start]);
	}
	else if (!(redr->red_type & (READ_FCUSFD | READ_FILE
			| HERE_STRING | HERE_DOC | RDWR_TF)))
		redr->left_fd = 1;
	return (1);
}

static int		stock_rfd(t_utils *utils, t_redirections *redr, size_t *end)
{
	(*end) += ft_skip_sep(&utils->arg[*end], "><&");
	if (redr->red_type & (SWAP_LFD_TRFD | READ_FCUSFD))
	{
		if (get_right_side(utils, end, &redr->file_name) == -1)
			return (-1);
		redr->right_fd = ft_atoi(redr->file_name);
		if (utils->arg[*end] == '-' && !ft_strcmp(redr->file_name, "-"))
			redr->red_type = CLOSE_LFD;
		else if (utils->arg[*end] == '-')
			redr->red_type |= CLOSE_RFD;
		(utils->arg[*end] == '-') ? (*end)++ : 0;
		ft_strdel(&redr->file_name);
	}
	return (1);
}

static int		stock_file_name(t_utils *utils,
		t_redirections *redr, size_t *end)
{
	char *tmp;

	if ((redr->red_type &
		(APPEN_TF | HERE_STRING | HERE_DOC | TRUNC_TF | RDWR_TF | READ_FILE)))
	{
		if (utils->arg[*end])
			redr->file_name = ft_strdup(&utils->arg[*end]);
		else if (
		!(redr->file_name = get_next_arg(&utils->cmd, &utils->index_arg)))
			return (is_near(0));
		if (type_of_argument(redr->file_name, 0))
			return (is_near(type_of_argument(redr->file_name, 0)));
		tmp = redr->file_name;
		redr->file_name =
			ft_strndup_shell(redr->file_name, ft_strlen(redr->file_name));
		free(tmp);
		*end = ft_strlen(utils->arg);
		if (validate_arg(redr->file_name, utils->index_arg) == -1)
			return (-1);
	}
	if ((redr->red_type & (HERE_DOC)))
		read_herdoc(&redr->file_name);
	if (!redr->file_name && (redr->red_type & (HERE_DOC | HERE_STRING)))
		redr->file_name = ft_strnew(0);
	return (1);
}

int				cut_if_redoraggr(t_redirections **red_aggr, t_utils *utils)
{
	size_t	end;
	size_t	start;

	if ((*red_aggr))
		cut_if_redoraggr(&(*red_aggr)->next, utils);
	if (((end = ft_strchr_index_shell(utils->arg, '<')) != -1
	|| (end = ft_strchr_index_shell(utils->arg, '>')) != -1)
	&& ((!end || utils->arg[end - 1] != '\\')))
	{
		start = end;
		if (!(*red_aggr = (t_redirections*)ft_memalloc(sizeof(t_redirections))))
			return (ft_perror("42sh: malloc"));
		if (((*red_aggr)->red_type =
			ret_red_type(utils->arg, end, utils->arg[end])) == -1)
			return (-1);
		if (stock_lfd(utils->arg, *red_aggr, &start) == -1)
			return (-1);
		if (stock_rfd(utils, *red_aggr, &end) == -1)
			return (-1);
		if (stock_file_name(utils, *red_aggr, &end) == -1)
			return (-1);
		join_rest_tocmd(utils->arg, start, end);
		return (cut_if_redoraggr(red_aggr, utils));
	}
	return (1);
}
