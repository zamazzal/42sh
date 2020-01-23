/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:36:09 by oboualla          #+#    #+#             */
/*   Updated: 2020/01/20 09:04:02 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/get_next_line.h"

void    complet_line(int balance, char **ptr, char **line_addrs)
{
    int     len;
    char    *prompt;
    char    *complet;
    char    *tmp;

    if (balance == 1)
        prompt = "dquote> ";
    if (balance == 2)
        prompt = "quote> ";
    if (balance == 4)
        prompt = "> ";
    complet = readline(prompt);
    tmp = *line_addrs;
    *line_addrs = ft_strjoin(tmp, "\n");
    *ptr = &(*line_addrs)[(ft_strlen(*line_addrs) - ft_strlen(*ptr) - 1)];
    free(tmp);
    tmp = *line_addrs;
    *line_addrs = ft_strjoin(tmp, complet);
    *ptr = &(*line_addrs)[(ft_strlen((*line_addrs)) - ft_strlen(complet) - ft_strlen(*ptr))];
    free(tmp);
    free(complet);
}

char    *ft_strndup_shell(char *cmd, size_t n)
{
    char *str;
    size_t i;
    size_t j;
    size_t balance = 0;

    j = 0;
    i = 0;
    if (!(str = (char *)ft_memalloc(sizeof(char) * (ft_strlen(cmd) + 1))))
        return (NULL);
    while (cmd[i] && i < n)
    {
        if (cmd[i] == '"' && (!i || cmd[i - 1] != '\\') && !(balance & 2))
            balance = (balance > 0) ? 0 : 1;
        else if (cmd[i] == '\'' && (!i || cmd[i - 1] != '\\') && !(balance & 1))
            balance = (balance > 0) ? 0 : 2;
        if (cmd[i] == '\\' && (!i || cmd[i - 1] != '\\'))
            i++;
        if (cmd[i] == '"' && (!i || cmd[i - 1] != '\\') && (balance == 1 || !balance))
            i++;
        if (cmd[i] == '\'' && (!i || cmd[i - 1] != '\\') && (balance == 2 || !balance))
            i++;
        str[j] = cmd[i];
        j++; 
        i++;
    }
    return (str);
}

char    *stock_next_argument(char *cmd, size_t *end_argument, char **line_addr)
{
    char    *next_argument;
    size_t  i;
    size_t  balance;

    if (!cmd || !cmd[0])
        return (NULL);
    balance = 0;
    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '"' && (!i || cmd[i - 1] != '\\') && !(balance & 2))
            balance = (balance > 0) ? 0 : 1;
        else if (cmd[i] == '\'' && (!i || cmd[i - 1] != '\\') && !(balance & 1))
            balance = (balance > 0) ? 0 : 2;
        else if (cmd[i] == '(' && (!i || cmd[i - 1] != '\\') && !balance)
            balance = 4;
        else if (cmd[i] == ')' && (!i || cmd[i - 1] != '\\') && (balance & 4))
            balance = 0;
        else if (cmd[i] == ' ' && (!i || cmd[i - 1] != '\\') && !balance)
            break ;
        else if (!balance && ((type_of_argument(cmd, i)) != 0))
        {
            if (!i && (i = 1) && (cmd[i] == cmd[i - 1] || cmd[i] == cmd[i - 1] || cmd[i] == cmd[i - 1]))
                i++;
            break ;
        }
        i++;
        if (balance && !cmd[i])
            complet_line(balance, &cmd, line_addr);
    }
    next_argument = ft_strndup(&cmd[ft_skip_sep(cmd, " \t")], i - ft_skip_sep(cmd, " \t"));
    *end_argument = i;
    return (next_argument);
}

int      ft_strchr_index_shell(char *cmd, char c)
{
    size_t i;
    size_t balance;

    balance = 0;
    i = 0;
    if (!cmd)
        return (-1);
    while (cmd[i])
    {
        if (cmd[i] == '"' && (!i || cmd[i - 1] != '\\') && !(balance & 2))
            balance = (balance > 0) ? 0 : 1;
        else if (cmd[i] == '\'' && (!i || cmd[i - 1] != '\\') && !(balance & 1))
            balance = (balance > 0) ? 0 : 2;
        else if (cmd[i] == c && (!i || cmd[i - 1] != '\\') && !balance)
            break ;
        i++;
    }
    if (cmd[i] == c)
        return (i);
    return (-1);
}

void    argument_join(char **cmd, char *argument)
{
    char    *tmp;

    if (!*cmd)
        *cmd = ft_strdup(argument);
    else
    { 
        tmp = *cmd;
        *cmd = ft_strjoin(tmp, " ");
        ft_strdel(&tmp);
        tmp = *cmd;
        *cmd = ft_strjoin(*cmd, argument);
        ft_strdel(&tmp);
    }
}