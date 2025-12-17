# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/17 13:00:00 by esouhail          #+#    #+#              #
#    Updated: 2025/12/17 16:37:09 by esouhail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc
MLX_DIR		= lib/minilibx-linux

# Source files
SRC_FILES	= main.c \
		parser/parser.c \
		parser/parse_ambient.c \
		parser/parse_camera.c \
		parser/parse_light.c \
		parser/parse_sphere.c \
		parser/parse_plane.c \
		parser/parse_cylinder.c \
		parser/parse_color.c \
		parser/parse_vector.c \
		math/vector_ops.c \
		math/vector_utils.c \
		intersect/sphere.c \
		intersect/plane.c \
		intersect/trace.c \
		render/camera.c \
		render/render.c \
		render/ray.c \
		utils/count_split.c \
		utils/free_split.c \
		utils/ft_atoi.c \
		utils/ft_isdigit.c \
		utils/ft_memcpy.c \
		utils/ft_split.c \
		utils/ft_strlen.c \
		utils/ft_strncmp.c \
		utils/ft_strtod.c \
		utils/get_next_line.c \
		utils/linked_list_operations.c \
		utils/print_error.c \
		mlx/cleanup.c \
		mlx/hooks.c \
		mlx/init_mlx.c \
		mlx/put_pixel.c \
		mlx/render.c \


SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR)
DEFINES		= -D_USE_MATH_DEFINES

# Libraries
MLX_LIB		= $(MLX_DIR)/libmlx.a
LIBS		= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Colors for output
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

# Rules
all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(MLX_DIR) clean > /dev/null 2>&1

fclean: clean
	rm -f $(NAME)

re: fclean all

# Run with test scene
test: all
	./$(NAME) test.rt

# Check for norm errors
norm:
	norminette $(SRC_DIR) $(INC_DIR) || true

# Debug build with debug symbols and no optimization
debug: CFLAGS += -g3 -O0 -DDEBUG
debug: re

# Valgrind memory check
valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) test.rt

# Help
help:
	@echo "$(GREEN)MiniRT Makefile Commands:$(RESET)"
	@echo "  make          - Build the project"
	@echo "  make clean    - Remove object files"
	@echo "  make fclean   - Remove object files and executable"
	@echo "  make re       - Rebuild the project"
	@echo "  make test     - Build and run with test.rt"
	@echo "  make norm     - Check code with norminette"
	@echo "  make debug    - Build with debug flags"
	@echo "  make valgrind - Run with valgrind memory checker"

.PHONY: all clean fclean re test norm debug valgrind help
