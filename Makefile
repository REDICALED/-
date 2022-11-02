# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 08:53:03 by jinhokim          #+#    #+#              #
#    Updated: 2022/11/02 15:13:42 by jinhokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c \
		utils.c \
		list_utils.c \

CC = cc
FLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RM = rm -rf

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

re: fclean all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: all clean fclean re
