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

NAME = readline.a
libft_file = libft.a


FLAGS  = -Wall -Wextra -Werror

Libft = 		-L $(LIBFT_PATH) -lft

Includes = includes/
Sources = sources/
Objects = objects/
libft_path = libft/

HEADERS= -I $(Includes) -I $(addprefix $(libft_path), $(Includes))

FILES =		fc_built_check.c			\
			fc_built_e.c				\
			fc_built_l.c				\
			ft_copy_cut.c				\
			ft_cursor_move.c			\
			ft_cursor_tab.c				\
			ft_delect_char.c			\
			ft_history_expansion1.c		\
			ft_history_expansion2.c		\
			ft_history_expension.c		\
			ft_history_save.c			\
			ft_incremental_search.c		\
			ft_initialize.c				\
			ft_key_detect.c				\
			ft_line_manage.c			\
			ft_manage_history.c			\
			ft_move_addition.c			\
			ft_move_addition1.c			\
			ft_readline.c				\
			ft_sig_handlers.c			\
			ft_tools.c					\
			ft_tools2.c

SRCS = $(addprefix $(Sources), $(FILES))
OBJS = $(addprefix $(Objects), $(FILES:.c=.o))
LIBFT_LIB = $(addprefix $(libft_path), $(libft_file))

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@ar rc $(NAME) $(OBJS)

$(Objects)%.o: $(Sources)%.c
	@mkdir -p $(Objects)
	@gcc -c $(HEADERS) $< -o $@

$(LIBFT_LIB) :
	@Make -C $(libft_path)

clean :
	@make -C libft clean
	@/bin/rm -rf $(Objects)

fclean : clean
	@make -C libft fclean
	@/bin/rm -rf $(NAME)

re : fclean all

.PHONY: all, clean, fclean, re