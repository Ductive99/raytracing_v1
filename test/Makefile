# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#              #
#    Updated: 2025/12/12 01:11:02 by abendrih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC_DIR = ../src
INC_DIR = ../inc
PARSER_DIR = $(SRC_DIR)/parser
UTILS_DIR = $(SRC_DIR)/utils

SRCS = main.c \
       $(PARSER_DIR)/parser.c \
       $(PARSER_DIR)/parse_ambient.c \
       $(PARSER_DIR)/parse_camera.c \
       $(PARSER_DIR)/parse_light.c \
       $(PARSER_DIR)/parse_sphere.c \
       $(PARSER_DIR)/parse_plane.c \
       $(PARSER_DIR)/parse_cylinder.c \
       $(PARSER_DIR)/parse_color.c \
       $(PARSER_DIR)/parse_vector.c \
       $(UTILS_DIR)/ft_strlen.c \
       $(UTILS_DIR)/ft_strncmp.c \
       $(UTILS_DIR)/ft_atoi.c \
       $(UTILS_DIR)/ft_strtod.c \
       $(UTILS_DIR)/ft_split.c \
       $(UTILS_DIR)/ft_memcpy.c \
       $(UTILS_DIR)/ft_isdigit.c \
       $(UTILS_DIR)/free_split.c \
       $(UTILS_DIR)/count_split.c \
       $(UTILS_DIR)/get_next_line.c \
       $(UTILS_DIR)/linked_list_operations.c \
       $(UTILS_DIR)/print_error.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)
LDFLAGS = -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
