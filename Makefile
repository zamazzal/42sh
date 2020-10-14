# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helmanso <helmanso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 14:09:21 by zamazzal          #+#    #+#              #
#    Updated: 2020/02/16 04:04:20 by oboualla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			42sh

FLAGS =			-Wall -Wextra -Werror

SRCS_PATH = 	sources/
OBJ_PATH = 		objects/

TERMCAP = 		-ltermcap
LIBFT_PATH = 	libft/
Libft = 		-L $(LIBFT_PATH) -lft
LIBFT_HEADER	= $(LIBFT_PATH)/includes
INCLUDES = 		-I includes/ -I $(LIBFT_HEADER)
HEADER = 		includes/mysh.h

builtins_SRCS = 	$(addprefix $(SRCS_PATH), builtins/)
execution_SRCS = 	$(addprefix $(SRCS_PATH), execution/)
expantions_SRCS = 	$(addprefix $(SRCS_PATH), expantions/)
readline_SRCS = 	$(addprefix $(SRCS_PATH), readline/)
shell_SRCS = 		$(addprefix $(SRCS_PATH), shell/)
tools_SRCS = 		$(addprefix $(SRCS_PATH), tools/)
parsing_SRCS = 		$(addprefix $(SRCS_PATH), parsing/)
vars_SRCS = 		$(addprefix $(SRCS_PATH), vars/)
jobs_control_SRCS = $(addprefix $(SRCS_PATH), jobs_control/)

builtins_OBJ = 		$(addprefix $(OBJ_PATH), builtins/)
execution_OBJ = 	$(addprefix $(OBJ_PATH), execution/)
expantions_OBJ = 	$(addprefix $(OBJ_PATH), expantions/)
readline_OBJ = 		$(addprefix $(OBJ_PATH), readline/)
shell_OBJ = 		$(addprefix $(OBJ_PATH), shell/)
tools_OBJ = 		$(addprefix $(OBJ_PATH), tools/)
parsing_OBJ = 		$(addprefix $(OBJ_PATH), parsing/)
vars_OBJ = 			$(addprefix $(OBJ_PATH), vars/)
jobs_control_OBJ =	$(addprefix $(OBJ_PATH), jobs_control/)

builtins =		access_file.c				\
				alias.c						\
				alias_exec.c				\
				alias_replace.c				\
				alias_sub.c					\
				fc_built_check.c			\
				fc_built_check3.c			\
				fc_built_check4.c			\
				fc_built_e.c				\
				fc_built_l.c				\
				fc_built_s.c				\
				ft_builtins.c				\
				ft_cd.c						\
				ft_cd_help.c				\
				ft_cd_options.c				\
				ft_echo.c					\
				ft_type.c					\
				ft_type_help.c				\
				ft_type_options.c			\
				get_cdpath.c				\
				hash.c						\
				hash_tools1.c				\
				hash_tools2.c				\
				test.c						\
				test_tools1.c				\
				test_tools2.c				\
				unalias.c					\
				fc_built_s1.c				\
				unalias_sub.c				\
				fc_built_add.c

execution =		child_jobs.c				\
				cmd_split.c					\
				exec.c						\
				exec_error.c				\
				exec_pipe.c					\
				exec_rederiction.c			\
				exec_utils.c				\
				parent_jobs.c				\
				proc_substitution.c			\
				signal_handl.c				\
				exec_error2.c				\
				exec_tools.c

expantions = 	expansion_sub.c				\
				expantions.c				\
				expantions_tools.c			\
				parameters.c				\
				parameters_sub.c			\
				parameters_tag.c			\
				tag_splitting.c

jobs_control =	bg_builtin.c				\
				fg_builtin.c				\
				jobs_builtins.c				\
				jobs_managment.c			\
				jobs_option.c				\
				jobs_utils.c				\
				jobs_utils2.c				\
				check_jobs.c				\
				inform_user.c

parsing =		complet_cmd.c				\
				convert_red_aggr.c			\
				free_lst_parse.c			\
				get_next_arg.c				\
				parse.c						\
				parse_oper.c				\
				parse_utils.c				\
				parsing_error.c				\
				reder_aggr_utils.c

readline =		ft_copy_cut.c				\
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
				ft_tools2.c					\
				ft_useless.c

shell =			shell.c						\
				shell_init.c

tools =			tools1.c					\
				tools2.c					\
				tools3.c

vars =			export.c					\
				export_tools.c				\
				getvars.c					\
				key_value.c					\
				set.c						\
				setvar.c					\
				unset.c						\
				var_instr.c					\
				var_instr_tools.c			\
				var_insrt_tools2.c


SRCS =	$(addprefix $(builtins_SRCS), $(builtins))					\
		$(addprefix $(execution_SRCS), $(execution))				\
		$(addprefix $(expantions_SRCS), $(expantions))				\
		$(addprefix $(readline_SRCS), $(readline))					\
		$(addprefix $(shell_SRCS), $(shell))						\
		$(addprefix $(tools_SRCS), $(tools))						\
		$(addprefix $(parsing_SRCS), $(parsing))					\
		$(addprefix $(vars_SRCS), $(vars))							\
		$(addprefix $(jobs_control_SRCS), $(jobs_control))			\

OBJ =	$(addprefix $(builtins_OBJ), $(builtins:.c=.o))				\
		$(addprefix $(execution_OBJ), $(execution:.c=.o))			\
		$(addprefix $(expantions_OBJ), $(expantions:.c=.o))			\
		$(addprefix $(readline_OBJ), $(readline:.c=.o))				\
		$(addprefix $(shell_OBJ), $(shell:.c=.o))					\
		$(addprefix $(tools_OBJ), $(tools:.c=.o))					\
		$(addprefix $(parsing_OBJ), $(parsing:.c=.o))				\
		$(addprefix $(vars_OBJ), $(vars:.c=.o))						\
		$(addprefix $(jobs_control_OBJ), $(jobs_control:.c=.o))		\

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(OBJ) $(Libft) $(INCLUDES) get_next_line/get_next_line.c -o $(NAME) $(TERMCAP)
	@echo "\x1B[96mBinary File \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(builtins_OBJ)%.o: $(builtins_SRCS)%.c $(HEADER)
	@mkdir -p $(builtins_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(execution_OBJ)%.o: $(execution_SRCS)%.c $(HEADER)
	@mkdir -p $(execution_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(expantions_OBJ)%.o: $(expantions_SRCS)%.c $(HEADER)
	@mkdir -p $(expantions_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(parsing_OBJ)%.o: $(parsing_SRCS)%.c $(HEADER)
	@mkdir -p $(parsing_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(readline_OBJ)%.o: $(readline_SRCS)%.c $(HEADER)
	@mkdir -p $(readline_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(jobs_control_OBJ)%.o: $(jobs_control_SRCS)%.c $(HEADER)
	@mkdir -p $(jobs_control_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(shell_OBJ)%.o: $(shell_SRCS)%.c $(HEADER)
	@mkdir -p $(shell_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(vars_OBJ)%.o: $(vars_SRCS)%.c $(HEADER)
	@mkdir -p $(vars_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(tools_OBJ)%.o: $(tools_SRCS)%.c $(HEADER)
	@mkdir -p $(tools_OBJ)
	@gcc -c $(FLAGS) $(INCLUDES) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

clean:
	@make -C $(LIBFT_PATH) clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\x1B[96mObjects Files \x1B[31mDeleted.\x1B[39;0m"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@/bin/rm -f $(NAME)
	@echo "\x1B[96mBinary File \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

re: fclean all

.PHONY: all, clean, fclean, re
