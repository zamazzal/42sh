/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 22:44:33 by oboualla          #+#    #+#             */
/*   Updated: 2019/06/18 04:58:58 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"

typedef struct		s_reste
{
	int				fd;
	char			*reste;
	struct s_reste	*next;
}					t_reste;

int					get_next_line(const int fd, char **line);

#endif
