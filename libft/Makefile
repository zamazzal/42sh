# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hessabra <hessabra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/02 20:23:02 by zamazzal          #+#    #+#              #
#    Updated: 2020/02/12 18:50:39 by zamazzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a 
H = libft.h
FLAGS = -Wall -Wextra -Werror

SRC_PATH = sources/
OBJ_PATH = objects/
INC_PATH = includes/

SRC = dfre.c dfree_int.c free_double.c ft_addtotab.c ft_atoi.c ft_bzero.c ft_entier.c ft_flags.c ft_freesub.c ft_freetab.c ft_printf_tools.c			\
	  ft_cased.c ft_cases.c ft_change_chr_to_nwchr.c ft_conversion.c ft_count_char.c ft_count_to_find.c ft_count_word.c	ft_existintab.c					\
	  ft_memmove.c ft_getchr.c ft_is_separ.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c ft_isspace.c					\
	  ft_isupper.c ft_itoa.c ft_jandf.c ft_lenth.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstlen.c ft_mmalloc.c	ft_memdel.c 			\
	  ft_tabtostr.c ft_delfromtab.c ft_lstmap.c ft_lstnew.c ft_max.c ft_mema.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c 			\
	  ft_memset.c ft_nbrdel.c ft_new_lst.c ft_parite.c ft_pathjoin.c ft_pourcent.c ft_precision.c ft_printf.c ft_putchar.c ft_putchar_fd.c				\
	  ft_putendl.c ft_putendl_fd.c ft_puthexa.c ft_putnbr.c ft_putnbr_fd.c ft_putoctal.c ft_putstr.c ft_putstr_fd.c ft_putstr_plus.c ft_putstr_to.c		\
	  ft_putstr_to_fd.c ft_putuint.c ft_rcased.c ft_remplacer_str.c ft_rev.c ft_reverse.c ft_searchnreplace.c ft_skip_lensep.c ft_skip_lensep.c			\
	  ft_skip_sep.c ft_split.c ft_split1.c ft_sqrt.c ft_strcat.c ft_strccmp.c ft_strccpy.c ft_strcdup.c ft_strchr.c ft_strclen.c ft_strclr.c			\
	  ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strmap.c ft_strmapi.c			\
	  ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strndup.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c		\
	  ft_strtrim.c ft_subtochar.c ft_tolower.c ft_toupper.c ft_white.c ft_width.c ft_wordlen.c print_arg.c splitbs.c tfree.c type_lower1.c type_upper.c	\

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
HEAD = $(addprefix $(INC_PATH), $(H))

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\x1B[96mLibft : \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) -I $(INC_PATH) -c $< -o $@

clean :
	@rm -rf $(OBJ_PATH)
	@echo "\x1B[96mLibft : \x1B[90;0m[\x1B[34;1m Objects \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\x1B[96mLibft : \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

re : fclean all

.PHONY: all, clean, fclean, re
