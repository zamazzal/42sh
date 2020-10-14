/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 22:44:33 by oboualla          #+#    #+#             */
/*   Updated: 2020/02/15 00:49:08 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUF_SZ 1

typedef struct		s_reste
{
	int				fd;
	char			*reste;
	struct s_reste	*next;
}					t_reste;

int					get_next_line(const int fd, char **line);

#endif
