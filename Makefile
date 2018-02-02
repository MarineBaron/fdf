# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:19:31 by mbaron            #+#    #+#              #
#    Updated: 2018/02/02 11:57:26 by mbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		fdf

DIR				=		.

DIR_SRCS		=		$(DIR)/srcs

DIR_HEADERS		=		$(DIR)/includes

DIR_LIB			=		$(DIR)/libft

DIR_LIB_HEADERS	=		$(DIR_LIB)/includes

LIB				=		-L$(DIR_LIB) -lft

HEADERS			=		-I$(DIR_HEADERS)			\
						-I$(DIR_LIB_HEADERS)

SRCS			=		$(DIR_SRCS)/main.c				\
						$(DIR_SRCS)/config.c			\
						$(DIR_SRCS)/config_file.c		\
						$(DIR_SRCS)/config_default.c	\
						$(DIR_SRCS)/map_init.c	\
						$(DIR_SRCS)/utils.c				\
						$(DIR_SRCS)/error.c

OBJS			=		$(SRCS:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer

RM				=		rm -f

all				:		$(NAME)

$(NAME)			:		$(OBJS)
						$(MAKE) -C $(DIR_LIB)
						$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(HEADERS) $(LIB)

%.o				:		%.c
						$(CC) -o $@ -c $< $(CFLAGS) $(HEADERS)

clean			:
						$(MAKE) -C $(DIR_LIB) clean
						$(RM) $(OBJS)

fclean			:		clean
						$(MAKE) -C $(DIR_LIB) fclean
						$(RM) $(NAME)

re				:		fclean all

.PHONY			: 		all clean fclean re libft
