# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnakahod <jnakahod@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/27 16:49:55 by jnakahod          #+#    #+#              #
#    Updated: 2021/03/20 18:31:48 by jnakahod         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS = srcs/cub3d.c \
		srcs/get_next_line.c \
		srcs/get_next_line_utils.c \
		srcs/init.c \
		srcs/exit.c \
		srcs/parse_line.c \
		srcs/parse_element.c \
		srcs/parse_map.c \
		srcs/flood_fill.c \
		srcs/utils.c \
		srcs/combine_data_from_map.c \

OBJCS = $(SRCS:%.c=%.o)

INCLUDE = ./includes

RM = rm -f

all: $(NAME)

$(NAME): $(OBJCS)
		$(MAKE) -C $(LIBFT_DIR) bonus
		$(CC) $(CFLAGS) -o $(NAME) -lm $(LIBFT_LIB) -I $(INCLUDE) $(OBJCS)

clean:
		$(MAKE) -C $(LIBFT_DIR) clean
		$(RM) $(OBJCS)

fclean:
		$(MAKE) -C $(LIBFT_DIR) fclean
		$(RM) $(OBJCS)
		$(RM) $(NAME)

re: fclean all

test:
		gcc -g    ./libft/libft.a -I ./includes/cub3d.h \
		srcs/cub3d.c \
		srcs/get_next_line.c \
		srcs/get_next_line_utils.c \
		srcs/init.c \
		srcs/exit.c \
		srcs/parse_line.c \
		srcs/parse_element.c \
		srcs/parse_map.c \
		srcs/flood_fill.c \
		srcs/utils.c \
		srcs/combine_data_from_map.c \

.PHONY: all clean fclean re test
