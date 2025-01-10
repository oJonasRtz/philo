# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 10:43:40 by jopereir          #+#    #+#              #
#    Updated: 2025/01/08 12:06:16 by jopereir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
SRCS = 
	
SRC = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJ = $(SRC:.c=.o)
HEADER = include

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(HEADER) -g

all: $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling $(NAME)"
	@$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(OBJ) -pthread -o $(NAME)

leak: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 2>&1 | \
	grep -i "no leaks are possible" > /dev/null && echo "Everything is OK." || echo "Leak found!!!"

clean:
	@echo "Objects removed."
	@rm -f $(OBJ)

fclean: clean
	@echo "$(NAME) removed."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
