# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:19:31 by mbaron            #+#    #+#              #
#    Updated: 2018/02/01 09:32:31 by mbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		fdf

DIR				=		.

DIR_SRCS		=		$(DIR)/srcs

DIR_HEADERS		=		$(DIR)/includes

DIR_LIB			=		$(DIR)/libft

DIR_LIB_HEADERS	=		$(DIR_LIB)

LIB				=		-L$(DIR_LIB) -lft

HEADERS			=		-I$(DIR_HEADERS)	\
						-I$(DIR_LIB_HEADERS)

SRCS			=		$(DIR_SRCS)/main.c

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
