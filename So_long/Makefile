# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clu <clu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 22:37:50 by clu               #+#    #+#              #
#    Updated: 2025/02/11 23:27:27 by clu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Name
NAME = so_long

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
# MLX42 requires linking against glfw and macOS frameworks:
MLX_FLAGS = -lglfw -ldl -lpthread -lX11 -lXrandr -lXinerama -lXcursor -lGL

# Include Directories:
# Combine your project-specific headers with those from GLFW and Libft.
INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(shell brew --prefix glfw)/include

# Directories
SRC_DIR 	= srcs
OBJ_DIR 	= obj
LIBFT_DIR 	= libft
MLX42_DIR 	= ./MLX42/build

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX42 = $(MLX42_DIR)/libmlx42.a
INCLUDES += -I./MLX42/include/MLX42

# GLFW (installed via brew)
GLFW_PATH = $(shell brew --prefix glfw)
LD_FLAGS = -L$(GLFW_PATH)/lib

# MLX42
MLX42_DIR = ./MLX42/build
MLX42 = ${MLX42_DIR}/libmlx42.a

# Source files
SRCS = so_long.c \

# Source files: all .c files in SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Object files go into OBJ_DIR, preserving the same filename
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	@echo "Creating executable $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(MLX_FLAGS) $(LD_FLAGS) -o $(NAME)

# Compile source files into objects.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)

# Build MLX42 if it does not exist.
$(MLX42):
	@if [ ! -f "$(MLX42)" ]; then \
		echo "Building MLX42..."; \
		cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "Removing executable $(NAME)..."
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
