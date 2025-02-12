# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clu <clu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 22:37:50 by clu               #+#    #+#              #
#    Updated: 2025/02/12 16:51:45 by clu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Name
NAME = so_long

# Comiler and Flags
CC 		= cc
CFLAGS 	= -Wall -Werror -Wextra

# Directories
SRC_DIR 	= src
OBJ_DIR 	= obj
LIBFT_DIR 	= libft
MLX42_DIR	= MLX42
GLFW_DIR 	:= $(MLX42_DIR)/build/_deps/glfw-build/src

# Libraries
LIBFT	:= $(LIBFT_DIR)/libft.a
MLX42	:= $(MLX42_DIR)/build/libmlx42.a
GLFW	:= $(GLFW_DIR)/libglfw3.a
LIBS	:= $(LIBFT) $(MLX42) $(GLFW) -lX11 -lXrandr -lXinerama -lXcursor \
		-lXi -ldl -pthread -lm

# Source files
SRC =	so_long.c \

HEADERS = -Iincludes -I$(MLX42_DIR)/include/MLX42 -I$(LIBFT_DIR)
SRC 	:= $(addprefix $(SRC_DIR)/, $(SRC))
OBJ 	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX42)
	@echo "Building executable $(NAME) ..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "Done"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)
	@echo "Done"

$(MLX42):
	@echo "Building MLX42..."
	@cmake -B $(MLX42_DIR)/build $(MLX42_DIR)
	@cmake --build $(MLX42_DIR)/build -j4
	@echo "MLX42 build complete."

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX42_DIR)/build
	@echo "Cleaned up all object files"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "Cleaned up $(NAME)"
	@echo "Cleaned up everything"

re: fclean all
	@echo "Remade everything"

.PHONY: all clean fclean re
