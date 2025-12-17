# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#              #
#    Updated: 2025/12/17 14:53:09 by abendrih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# Directories
SRC_DIR = src
INC_DIR = inc
PARSER_DIR = $(SRC_DIR)/parser
UTILS_DIR = $(SRC_DIR)/utils
MLX_DIR = $(SRC_DIR)/mlx
MATH_DIR = $(SRC_DIR)/math
INTERSECT_DIR = $(SRC_DIR)/intersect
MINILIBX_DIR = minilibx-linux

# Source files
SRCS = $(SRC_DIR)/main.c \
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
       $(UTILS_DIR)/print_error.c \
       $(MLX_DIR)/init_mlx.c \
       $(MLX_DIR)/hooks.c \
       $(MLX_DIR)/cleanup.c \
       $(MLX_DIR)/put_pixel.c \
       $(MLX_DIR)/render.c \
       $(INTERSECT_DIR)/sphere.c \
       $(INTERSECT_DIR)/plane.c \
       $(MATH_DIR)/vector_ops.c \
       $(MATH_DIR)/vector_utils.c \
       $(MATH_DIR)/ray.c

OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I$(INC_DIR) -I$(MINILIBX_DIR)
LDFLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm

# Colors for output
GREEN = \033[0;32m
RESET = \033[0m

# Rules
all: $(NAME)

$(MINILIBX_DIR)/libmlx.a:
	@echo "$(GREEN)Compiling MiniLibX...$(RESET)"
	@$(MAKE) -C $(MINILIBX_DIR) > /dev/null 2>&1

$(NAME): $(MINILIBX_DIR)/libmlx.a $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@$(MAKE) -C $(MINILIBX_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(GREEN)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
