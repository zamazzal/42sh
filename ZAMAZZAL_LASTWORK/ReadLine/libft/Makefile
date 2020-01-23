# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeFile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 15:27:47 by zamazzal          #+#    #+#              #
#    Updated: 2020/01/23 15:27:48 by zamazzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS  = -Wall -Wextra -Werror
Includes = includes/
Sources = sources/
Objects = objects/

FILES =		dfre.c			\
			dfree_int.c		\
			ft_addtotab.c	\
			ft_atoi.c		\
			ft_bzero.c		\
			ft_cased.c		\
			ft_cases.c		\
			ft_conversion.c	\
			ft_entier.c		\
			ft_flags.c		\
			ft_freesub.c	\
			ft_freetab.c	\
			ft_isalnum.c	\
			ft_isalpha.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_islower.c	\
			ft_isprint.c	\
			ft_isspace.c	\
			ft_isupper.c	\
			ft_itoa.c		\
			ft_jandf.c		\
			ft_lenth.c		\
			ft_lstadd.c		\
			ft_lstdel.c		\
			ft_lstdelone.c	\
			ft_lstiter.c	\
			ft_lstlen.c		\
			ft_lstmap.c		\
			ft_lstnew.c		\
			ft_max.c		\
			ft_mema.c		\
			ft_memalloc.c	\
			ft_memccpy.c	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_memcpy.c		\
			ft_memdel.c		\
			ft_memmove.c	\
			ft_memset.c		\
			ft_nbrdel.c		\
			ft_parite.c		\
			ft_pourcent.c	\
			ft_precision.c	\
			ft_printf.c		\
			ft_putchar.c	\
			ft_putchar_fd.c	\
			ft_putendl.c	\
			ft_putendl_fd.c	\
			ft_putnbr.c		\
			ft_putnbr_fd.c	\
			ft_putstr.c		\
			ft_putstr_fd.c	\
			ft_rcased.c		\
			ft_searchnreplace.c		\
			ft_split.c		\
			ft_split1.c		\
			ft_strcat.c		\
			ft_strchr.c		\
			ft_strclr.c		\
			ft_strcmp.c		\
			ft_strcpy.c		\
			ft_strdel.c		\
			ft_strdup.c		\
			ft_strequ.c		\
			ft_striter.c	\
			ft_striteri.c	\
			ft_strjoin.c	\
			ft_strlcat.c	\
			ft_strlen.c		\
			ft_strmap.c		\
			ft_strmapi.c	\
			ft_strncat.c	\
			ft_strncmp.c	\
			ft_strncpy.c	\
			ft_strnequ.c	\
			ft_strnew.c		\
			ft_strnstr.c	\
			ft_strrchr.c	\
			ft_strsplit.c	\
			ft_strstr.c		\
			ft_strsub.c		\
			ft_strtrim.c	\
			ft_subtochar.c	\
			ft_tablen.c		\
			ft_tolower.c	\
			ft_toupper.c	\
			ft_white.c		\
			ft_width.c		\
			splitbs.c		\
			tfree.c	

SRCS = $(addprefix $(Sources), $(FILES))
OBJS = $(addprefix $(Objects), $(FILES:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)

$(Objects)%.o: $(Sources)%.c
	@mkdir -p $(Objects)
	@gcc -c $(FLAGS) -I $(Includes) $< -o $@

clean :
	@/bin/rm -rf $(Objects)

fclean : clean
	@/bin/rm -rf $(NAME)

re : fclean all

.PHONY: all, clean, fclean, re