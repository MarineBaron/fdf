# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaron <mbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/24 09:32:18 by mbaron            #+#    #+#              #
#    Updated: 2018/02/01 13:44:06 by mbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#    Updated: 2018/01/23 08:31:15 by mbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=		libft.a

DIR				=		.

DIR_HEADERS		=		./includes

SRCS			=	$(DIR)/ft_memset.c			$(DIR)/ft_bzero.c			\
					$(DIR)/ft_memcpy.c			$(DIR)/ft_memccpy.c			\
					$(DIR)/ft_memmove.c			$(DIR)/ft_memchr.c			\
					$(DIR)/ft_memcmp.c			$(DIR)/ft_strlen.c			\
					$(DIR)/ft_strdup.c			$(DIR)/ft_strcpy.c			\
					$(DIR)/ft_strncpy.c			$(DIR)/ft_strcat.c			\
					$(DIR)/ft_strncat.c			$(DIR)/ft_strlcat.c			\
					$(DIR)/ft_strchr.c			$(DIR)/ft_strrchr.c			\
					$(DIR)/ft_strstr.c			$(DIR)/ft_strnstr.c			\
					$(DIR)/ft_strcmp.c			$(DIR)/ft_strncmp.c			\
					$(DIR)/ft_atoi.c			$(DIR)/ft_isalpha.c			\
					$(DIR)/ft_isdigit.c			$(DIR)/ft_isalnum.c			\
					$(DIR)/ft_isprint.c			$(DIR)/ft_isascii.c			\
					$(DIR)/ft_toupper.c			$(DIR)/ft_tolower.c			\
					$(DIR)/ft_memalloc.c		$(DIR)/ft_memdel.c			\
					$(DIR)/ft_strnew.c			$(DIR)/ft_strdel.c			\
					$(DIR)/ft_strclr.c			$(DIR)/ft_striter.c			\
					$(DIR)/ft_striteri.c		$(DIR)/ft_strmap.c			\
					$(DIR)/ft_strmapi.c			$(DIR)/ft_strequ.c			\
					$(DIR)/ft_strnequ.c			$(DIR)/ft_strsub.c			\
					$(DIR)/ft_strjoin.c			$(DIR)/ft_strtrim.c			\
					$(DIR)/ft_strsplit.c		$(DIR)/ft_itoa.c			\
					$(DIR)/ft_putchar.c			$(DIR)/ft_putstr.c			\
					$(DIR)/ft_putendl.c			$(DIR)/ft_putnbr.c			\
					$(DIR)/ft_putchar_fd.c		$(DIR)/ft_putstr_fd.c		\
					$(DIR)/ft_putendl_fd.c		$(DIR)/ft_putnbr_fd.c		\
					$(DIR)/ft_lstnew.c			$(DIR)/ft_lstdelone.c		\
					$(DIR)/ft_lstdel.c			$(DIR)/ft_lstadd.c			\
					$(DIR)/ft_lstiter.c			$(DIR)/ft_lstmap.c			\
					$(DIR)/ft_mba_lstnew.c		$(DIR)/ft_mba_lst2new.c		\
					$(DIR)/ft_mba_lst2delone.c								\
					$(DIR)/ft_mba_lst2add.c		$(DIR)/ft_mba_lst2del.c		\
					$(DIR)/ft_mba_lstaddafter.c	$(DIR)/ft_mba_lst2addafter.c \
					$(DIR)/ft_mba_lstfind.c		$(DIR)/ft_mba_lst2find.c	\
					$(DIR)/ft_mba_lstremone.c	$(DIR)/ft_mba_lst2remone.c	\
					$(DIR)/ft_mba_lstlen.c		$(DIR)/ft_mba_lst2len.c		\
					$(DIR)/ft_putstr_array.c	$(DIR)/get_next_line.c

OBJS			=		$(SRCS:.c=.o)

CC				=		gcc

CFLAGS			=		-Wall -Werror -Wextra

RM				=		rm -f

all				:		$(NAME)

$(NAME)			:		$(OBJS)
						ar rc $(NAME) $(OBJS)
						ranlib $(NAME)

$(OBJS)			:		$(SRCS)
						$(CC) -c $(SRCS) -I $(DIR_HEADERS) $(CFLAGS)

clean			:
						$(RM) $(OBJS)

fclean			:		clean
						$(RM) $(NAME) $(LIB)

re				:		fclean all

.PHONY			:  all clean fclean re
