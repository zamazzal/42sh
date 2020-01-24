/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cased.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hessabra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:28:44 by hessabra          #+#    #+#             */
/*   Updated: 2019/02/04 22:31:45 by hessabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_CASED_H
# define _FT_CASED_H

typedef struct	s_need5
{
	int i;
	int c;
	int	mc;
}				t_need5;

char			*ft_strrv(char *dest, const char *src);
char			*ft_strcp(char *dest, const char *src, int a);
char			sign(int x);

#endif
