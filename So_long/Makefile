# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clu <clu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 22:37:50 by clu               #+#    #+#              #
#    Updated: 2025/03/03 14:59:35 by clu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Name
NAME = so_long

# Comiler and Flags
CC 		= cc
CFLAGS 	= -Wall -Werror -Wextra

# Directories
SRC_DIR 	= ./src
OBJ_DIR 	= ./obj
LIBFT_DIR 	= ./libft
MLX_DIR		= ./MLX42

# Libraries
LIBFT	:= $(LIBFT_DIR)/libft.a
LIBMLX	:= $(MLX_DIR)/build/libmlx42.a
LIBS	:= $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm

# Include directories
HEADERS = -I./include -I$(LIBFT_DIR)/include -I$(MLX_DIR)/include/MLX42
HEADERS_DEP := include/so_long.h

# Source files and object files
# shell runs the command inside it and returns the output
SRC = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all: $(MLX_DIR) $(LIBFT) $(NAME)

# Build the executable
$(NAME): $(OBJ)
	@echo "Building executable $(NAME) ..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "Done"

# Compile the object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS_DEP)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# Compile the Libft library
$(LIBFT):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)
	@echo "Done"

# Compile the MLX42 library
$(MLX_DIR):
	@echo "Compiling MLX42..."
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4
	@echo "Done"

# Clean up object files
clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_DIR)/build
	@echo "Cleaned up all object files"

# Clean up everything
fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR) 
	@make -C $(LIBFT_DIR) fclean
	@echo "Cleaned up $(NAME)"
	@echo "Cleaned up everything"

# Remake everything
re: fclean all
	@echo "Remade everything"

# Phony
.PHONY: all clean fclean re
