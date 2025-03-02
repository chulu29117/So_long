/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:19:51 by clu               #+#    #+#             */
/*   Updated: 2025/02/27 17:35:06 by clu              ###   ########.fr       */
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
# include <string.h>
# include <errno.h>
# include <time.h>
# include <stdio.h>

/* Window dimensions and tile definitions */
# define TILE_SIZE 64
# define WALL '1'
# define COLLECT 'C'
# define COLLECTED 'X'
# define PLAYER 'P'
# define EXIT 'E'
# define FLOOR '0'
# define VISITED 'V'

/* Boolean values */
# define TRUE 1
# define FALSE 0

// Player struct storing the player's grid coordinates
typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

// Texture struct storing the texture data
typedef struct s_textures
{
	mlx_texture_t	*floor;
	mlx_texture_t	*wall;
	mlx_texture_t	*collectible;
	mlx_texture_t	*player;
	mlx_texture_t	*exit;
}	t_textures;

// Image struct storing the image data
typedef struct s_images
{
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*player;
	mlx_image_t	*exit;
}	t_images;

// Game struct storing the game data
typedef struct s_game
{
	mlx_t		*mlx;
	t_player	player;
	t_textures	*tex;
	t_images	*img;
	char		**map;
	char		**map_copy;
	int			move_count;
	int			map_rows;
	int			map_cols;
	int			map_height;
	int			map_width;
	int			collected;
	int			total_collected;
	int			finished;
	int			exit_found;
	int			collect_found;
}	t_game;

// Parsing map
void	size_map(t_game *game, char **map);
void	parse_map(char *file, t_game *game);
int		is_valid_filename(const char *file);
int		check_elements(t_game *game);
int		check_solvable(t_game *game);
int		validate_map(t_game *game);
int		set_player_start(t_game *game);

// Load_textures(t_game *game);
void	get_textures(t_game *game);
void	get_images(t_game *game);
void	draw_map(t_game *game, t_images *imag);

// Movements and events
void	count_collect(t_game *game);
void	move_player(t_game *game, int dx, int dy);
void	keyhook(mlx_key_data_t keydata, void *param);

// Free functions
void	free_map(char **map);
void	free_game(t_game *game);
void	free_parsing(t_game *game, char *file, char *msg);

// Error
void	exit_error(const char *msg);

#endif
