/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:19:51 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 13:58:45 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <memory.h>
# include <time.h>

/* Window dimensions and tile definitions */
# define HEIGHT	600
# define WIDTH 800
# define TILE_SIZE 64
# define MOVE 64
# define WALL '1'
# define COLLECT 'C'
# define PLAYER 'P'
# define EXIT 'E'
# define FLOOR '0'

/* Boolean values */
# define TRUE 1
# define FALSE 0

// Map structure holds the grid and its dimensions

// Player structure stores the player's grid coordinates
typedef struct s_player
{
	int		x;
	int		y;
}	t_player;

typedef struct	s_textures
{
	mlx_texture_t	*floor;
	mlx_texture_t	*wall;
	mlx_texture_t	*collectible;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;
}	t_textures;

typedef struct s_images
{
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*player;
	mlx_image_t	*exit;
}	t_images;

// 
typedef struct s_game
{
	mlx_t		*mlx;
	t_player	player;
	t_textures	*tex;
	t_images	*img;
	char		**map;
	int			move_count;
	int			player_instance;
	int			map_height;
	int			map_width;
}	t_game;


// Parsing map
void	parse_map(char *file, t_game *game);
int		validate_map(t_game *game);
void	set_player_start(t_game *game);

// Free functions
void	free_map(char **map);
void	free_game(t_game *game);

// Rendering
void	render_map(t_game *game);
// void	load_textures(t_game *game);
void	get_textures(t_game *game);
void	get_images(t_game *game);
void	draw_map(t_game *game, t_images *imag);

// Movements and events
void	move_player(t_game *game, int dx, int dy);
void	keyhook(mlx_key_data_t keydata, void *param);

// Error
void	exit_error(const char *msg);
int		print_error(const char *msg, int exit_code);

#endif
