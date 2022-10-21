# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: midfath <midfath@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 12:13:55 by abouhaga          #+#    #+#              #
#    Updated: 2022/10/21 17:48:20 by midfath          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



#Color:

RED		= \033[0;31m
DEFAULT	= \033[0;39m
PINK	= \033[1;35m
BLUE	= \033[1;34m

#vars

CC 			= gcc
CFLAGS 		= -Wall -Wextra -Werror  #-fsanitize=address -g
# CFLAGS 		= -Wall -Wextra -Werror
NAME 		= minishell
LIBFT    	= libft/libft.a
OBJ_DIR		= obj
BIN_DIR		= bin
BTIN_DIR	= builtin_src
NAME		= $(BIN_DIR)/$(BIN)
BIN			= minishell
SRC_DIR		= code
RDLINE		= -lreadline

#cmd

PRINTF		= printf

#src&&obj
SRC			=	ft_shell.c  ft_tokenize.c ft_strings_utils.c \
			  	ft_outfiles.c ft_lexer.c ft_lexer_utils.c ft_launch_shell.c \
			  	ft_last_io.c ft_infiles.c ft_heredoc.c ft_get_path.c ft_fill_args.c \
			  	ft_expand.c ft_expand_utils.c ft_errors.c \
		    	exe_data.c err_handling.c builtin_src/builtin_utils.c \
				builtin_src/cd_exe.c builtin_src/echo_exe.c builtin_src/env_exe.c \
				builtin_src/export_exe.c builtin_src/exit_exe.c builtin_src/pwd_exe.c \
				builtin_src/unset_exe.c exe_utils.c ft_exec.c exe_option.c
				

OBJS    	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all : $(NAME)

$(NAME) : $(BIN_DIR) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RDLINE) -I inc -o $(NAME)
	@$(PRINTF) "\r%100s\r$(BLUE)$(NAME) is up to date!$(DEFAULT)\n"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I inc -c $< -o $@
	@$(PRINTF) "\rCompiling $(BLUE)$<$(DEFAULT)..."

$(LIBFT):
	@make -C libft

$(BIN_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)/$(BTIN_DIR)

clean :
	@make clean -C libft

fclean : clean
	@rm -rf libft/libft.a
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)
	@$(PRINTF) "$(RED) $(NAME) removed successfully. $(DEFAULT)\n"

re : fclean all

.PHONY : all clean fclean 