# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clu <clu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 22:37:50 by clu               #+#    #+#              #
#    Updated: 2025/02/18 11:30:07 by clu              ###   ########.fr        #
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
LIBFT		:= $(LIBFT_DIR)/libft.a
LIBMLX		:= $(MLX_DIR)/build/libmlx42.a
LIBS		:= $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm

# Include directories
HEADERS = -I./includes -I$(MLX_DIR)/include/MLX42 -I$(LIBFT_DIR)

# Source files and object files
SRC 	= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ 	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libmlx $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "Building executable $(NAME) ..."
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "Done"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	
$(LIBFT):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)
	@echo "Done"

$(MLX_DIR):
	@echo "Compiling MLX42..."
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)
	@echo "Done"

libmlx: $(MLX_DIR)
	@echo "Building MLX42..."
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4
	@echo "MLX42 build complete."

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLX_DIR)/build
	@echo "Cleaned up all object files"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR) 
	@make -C $(LIBFT_DIR) fclean
	@echo "Cleaned up $(NAME)"
	@echo "Cleaned up everything"

re: fclean all
	@echo "Remade everything"

.PHONY: all clean fclean re libmlx
