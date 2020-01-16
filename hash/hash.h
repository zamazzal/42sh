/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 18:42:14 by zamazzal          #+#    #+#             */
/*   Updated: 2020/01/14 18:42:37 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "libft.h"
# include <dirent.h>

# define HTABLE_SIZE 1000000

typedef struct	s_hashtable
{
	int					hits;
	char				*cmd;
	char				*content;
	struct s_hashtable	*next;
}				t_hashtable;


typedef struct	s_hash
{
	t_hashtable *htable[HTABLE_SIZE];
    int *hashed;
    int hashed_nbr;
}				t_hash;

t_hash      g_hash;

# define SAFE(expr) if (!(expr)) return (0)

static int		ft_putin_htab(char *cmd, char *path);
void			ft_freeh_htab(void);

# endif
