/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rederiction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 02:30:20 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 18:51:01 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	bad_fd(int fd)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putnbr_fd(fd, 2);
	ft_putendl_fd(": bad file descriptor.", 2);
	return (-1);
}

static int	put_file_content(char *filename, int lfd, int pip[2], char **cmd)
{
	int fd;

	if (filename[0] == '(')
		return (proc_substitution_r(filename, pip, cmd));
	if (access(filename, F_OK))
	{
		ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putendl_fd(filename, 2);
		return (-1);
	}
	if ((fd = open(filename, O_RDONLY)) == -1 && ft_perror("42sh: open"))
		return (-1);
	dup2(fd, lfd);
	close(fd);
	return (1);
}

static int	trunc_or_append_to_file(t_redirections *redr, char **cal_cmd)
{
	int			fd;
	int			mode;

	if (redr->file_name[0] == '(')
		return (proc_substitution_w(redr->file_name, cal_cmd));
	if ((redr->red_type & RDWR_TF) && access(redr->file_name, F_OK))
	{
		ft_putstr_fd("42sh: ", 2);
		ft_perror(redr->file_name);
		return (0);
	}
	mode = (redr->red_type & (TRUNC_TF | RDWR_TF)) ? O_TRUNC : O_APPEND;
	if ((fd = open(redr->file_name, mode | O_WRONLY | O_CREAT,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1)
		return (ft_perror("42sh: open"));
	if (redr->red_type & REDR_STIN_STOUT)
	{
		dup2(fd, 1);
		dup2(fd, 2);
	}
	else
		dup2(fd, redr->left_fd);
	close(fd);
	return (1);
}

static int	if_redirection(t_redirections *red_agg, int pip[2], char **cmd)
{
	if ((red_agg->red_type & (HERE_DOC | HERE_STRING))
	&& red_agg->file_name && dup2(pip[0], red_agg->left_fd) != -1)
	{
		ft_putstr_fd(red_agg->file_name, pip[1]);
		(red_agg->red_type & HERE_STRING) ? ft_putchar_fd('\n', pip[1]) : 0;
	}
	if ((red_agg->red_type & (READ_FILE | RDWR_TF))
	&& (getpid() != g_shell_pid))
		if (put_file_content(red_agg->file_name,
		red_agg->left_fd, pip, cmd) == -1)
			return (-1);
	if ((red_agg->red_type & (TRUNC_TF | APPEN_TF | RDWR_TF)))
		if (trunc_or_append_to_file(red_agg, cmd) == -1)
			return (-1);
	if ((red_agg->red_type & SWAP_LFD_TRFD) &&
		(((red_agg->right_fd == pip[0]) || (red_agg->right_fd == pip[1]))
		|| dup2(red_agg->right_fd, red_agg->left_fd) == -1))
		return (bad_fd(red_agg->right_fd));
	return (1);
}

int			exec_redirection(t_redirections *red_agg, char **cmd)
{
	int pip[2];

	if (!red_agg)
		return (1);
	if (pipe(pip) == -1)
		return (ft_perror("42sh: pipe"));
	while (red_agg)
	{
		if (if_redirection(red_agg, pip, cmd) == -1)
			return (-1);
		if ((red_agg->red_type & (READ_FCUSFD)) &&
		(((red_agg->right_fd == pip[0])
		|| (red_agg->right_fd == pip[1])) || dup2(red_agg->right_fd, 0) == -1))
			return (bad_fd(red_agg->right_fd));
		if ((red_agg->red_type & CLOSE_LFD) && (close(red_agg->left_fd) == -1))
			return (bad_fd(red_agg->left_fd));
		if ((red_agg->red_type & CLOSE_RFD) && (close(red_agg->right_fd) == -1))
			return (bad_fd(red_agg->right_fd));
		red_agg = red_agg->next;
	}
	close(pip[0]);
	close(pip[1]);
	return (1);
}
