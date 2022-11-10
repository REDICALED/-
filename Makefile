# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 08:53:03 by jinhokim          #+#    #+#              #
#    Updated: 2022/11/10 17:42:11 by jinhokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR	:= ./srcs
INC_DIR	:= ./includes
OBJ_DIR	:= ./objects
LIB_DIR	:= ./libft

SRC = main.c \
		utils.c \
		tokenize.c \
		tokenize_count.c \
		tokenize_count2.c \
		hoo.c \
		hoo_here_doc.c \
		hoo_dollar.c \
		hoo_double_quote.c \
		hoo_string.c \
		redirection.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(OBJ) -L $(LIB_DIR) -lreadline -l ft -o $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(INC_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all
OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(OBJ) -L $(LIB_DIR) -lreadline -l ft -o $(NAME)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(INC_DIR) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all
