# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 16:56:31 by tfalchi           #+#    #+#              #
#    Updated: 2024/04/15 15:23:46 by tfalchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libftprintf.a

NAME = server
CLIENT = client
NAME_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SRCS_C = client.c
SRCS_S = server.c
SRCS_C_BONUS = client_bonus.c
SRCS_S_BONUS = server_bonus.c

all: server client

server:
	@make all -C $(LIBFT_DIR)
	@$(CC) $(SRCS_S) $(LIBFT) -o $(NAME)
	@echo "daje"
	
client:
	@make all -C $(LIBFT_DIR)
	@$(CC) $(SRCS_C) $(LIBFT) -o $(CLIENT)
	@echo "daje"

bonus:
	@make all -C $(LIBFT_DIR)
	@$(CC) $(SRCS_S_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@$(CC) $(SRCS_C_BONUS) $(LIBFT) -o $(CLIENT_BONUS)

clean:
	@make clean -C $(LIBFT_DIR)
	
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -f $(CLIENT) $(CLIENT_BONUS)

re: fclean all

redo:
	@$(CC) $(CFLAGS) $(SRCS_S) $(LIBFT) -o $(NAME)
	@$(CC) $(CFLAGS) $(SRCS_C) $(LIBFT) -o $(CLIENT)
	@echo "\033[35mDone !!\033[0m"

.PHONY: all clean fclean re redo