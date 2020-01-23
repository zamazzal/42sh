/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:46:54 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/21 22:20:14 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int  control_gprocess(int gpid)
{
    int fd;

    if (gpid == getpgrp())
    {
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
    }
    fd = open("/dev/tty", O_RDWR);
    if (tcsetpgrp(fd, gpid) == -1)
    {
        close(fd);
        if (gpid == getpgrp())
        {
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
        ft_perror("42sh: tcsetpgrp");
        return (-1);
    }
    close(fd);
    if (gpid == getpgrp())
    {
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }
    return (1);
}

int    parent_job(int pgid, int bg)
{
    int status;

    status = 0;
    while (!bg && waitpid(pgid * -1, &status, WUNTRACED) > 0)
        if (WIFSTOPPED(status))
            break ;
    if (!bg && control_gprocess(getpgrp()) == -1)
        return (-1);
    if (!bg)
    {
        if_signaled(status);
        if_suspend(status, pgid);
    }
    else
        if_background(pgid);
    return (status);
}

void    put_file_content(char *filename, char **env)
{
    char *argv[] = {"cat", filename, NULL};

    if (access(filename, F_OK))
    {
        ft_putstr_fd("42sh: no such file or directory: ", 2);
        ft_putendl_fd(filename, 2);
        exit(EXIT_FAILURE);
    }
    execve(get_path_cmd(argv[0], env), argv, env);
    exit (EXIT_FAILURE);
}

void    trunc_or_append_to_file(t_redirections *redr, int pip[2])
{
    int fd;

    if ((redr->red_type & PRINT_TO_FILE) && (fd = open(redr->file_name, O_WRONLY | O_TRUNC | O_CREAT , S_IRWXU | S_IRWXG | S_IROTH)) == -1)
    {
        ft_perror("42sh: open");
        exit(EXIT_FAILURE);
    }
    if ((redr->red_type & APP_TO_FILE) && (fd = open(redr->file_name, O_WRONLY | O_APPEND | O_CREAT , S_IRWXU | S_IRWXG | S_IROTH)) == -1)
    {
        ft_perror("42sh: open");
        exit(EXIT_FAILURE);
    }
    if (redr->red_type & REDIRECT_STDIN_STDOUT)
    {
        dup2(fd, 1);
        dup2(fd, 2);
    }
    else
        dup2(fd, redr->left_fd);
}

void    exec_redirection(t_redirections *rederction, char **env)
{
    int pip[2];

    if (!rederction)
        return ;
    if (pipe(pip) == -1)
        ft_perror("42sh: pipe");
    while (rederction)
    {
        if ((rederction->red_type & HERE_DOCUMENT || rederction->red_type & PRINT_NEXT_STRING) && dup2(pip[0], rederction->left_fd) != -1)
            ft_putstr_fd(rederction->file_name, pip[1]);
        else if (rederction->red_type & READ_FILE && rederction->file_name)
        {
            if (!fork())
            {
                close(pip[0]);
                dup2(pip[1], 1);
                close(pip[1]);
                put_file_content(rederction->file_name, env);
            }
        }
        else if ((rederction->red_type & PRINT_TO_FILE || rederction->red_type & APP_TO_FILE) && rederction->file_name)
            trunc_or_append_to_file(rederction, pip);
        if (rederction->red_type & CLOSE_LFD)
            close(rederction->left_fd);
        if (rederction->red_type & SWAP_LFD_T_RFD)
            if (dup2(rederction->right_fd, rederction->left_fd) == -1)
            {
                ft_putstr_fd("42sh: ", 2);
                ft_putnbr_fd(rederction->right_fd, 2);
                ft_putendl_fd(": bad file descriptor.", 2);
                exit(EXIT_FAILURE);
            }
        rederction = rederction->next;
    }
    close(pip[0]);
    close(pip[1]);
}

void    child_job(t_parse *lst, char **environ, int pip[2], int oldpr, int proc_nbr)
{
    char **argv;

    if (lst->pipe || proc_nbr > 0)
        close(pip[0]);
    if (proc_nbr != 0)
        dup2(oldpr, 0);
    if (lst->pipe)
        dup2(pip[1], 1);
    if (lst->pipe || proc_nbr > 0)
        close(pip[1]);
    argv = ms_parse(lst->cmd);
    exec_redirection(lst->lst_reder_aggr, environ);
    execve(get_path_cmd(argv[0], environ), argv, environ);
    exit (EXIT_FAILURE);
}