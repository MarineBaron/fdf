# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:19:31 by mbaron            #+#    #+#              #
#    Updated: 2018/02/04 23:13:07 by mbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		fdf

DIR				=		.

DIR_SRCS		=		$(DIR)/srcs

DIR_HEADERS		=		$(DIR)/includes

DIR_LIB			=		$(DIR)/libft

DIR_LIB_HEADERS	=		$(DIR_LIB)/includes

DIR_MLX			=		$(DIR)/minilibx

DIR_MLX_HEADERS	=		$(DIR_MLX)

INC				=		/usr/include

INCLIB			=		$(INC)/../lib

LIB				=		-L$(DIR_LIB) -lft

MLX				=		-L$(DIR_MLX) -lmlx_Linux -L$(INCLIB) -lXext -lX11 -lm -lbsd

HEADERS			=		-I$(DIR_HEADERS)			\
						-I$(DIR_LIB_HEADERS)		\
						-I$(DIR_MLX_HEADERS)		\
						-I$(INC) -O3

SRCS			=		$(DIR_SRCS)/main.c				\
						$(DIR_SRCS)/config.c			\
						$(DIR_SRCS)/config_file.c		\
						$(DIR_SRCS)/config_default.c	\
						$(DIR_SRCS)/config_map.c		\
						$(DIR_SRCS)/mlx_control.c	\
						$(DIR_SRCS)/mlx_map.c		\
						$(DIR_SRCS)/utils.c				\
						$(DIR_SRCS)/error.c

OBJS			=		$(SRCS:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Wextra -g

RM				=		rm -f

all				:		$(NAME)

$(NAME)			:		$(OBJS)
						$(MAKE) -C $(DIR_LIB)
						$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(HEADERS) \
						$(LIB) $(MLX)

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
