/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:19:51 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 21:12:29 by clu              ###   ########.fr       */
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
# include <stdbool.h>

# define PIXELS 64

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		start;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		map;
	t_player	player;
	void		*img_wall;
	void		*img_collectible;
	void		*img_floor;
	void		*img_player;
	void		*img_exit;
}	t_game;

// Parsing map
void	parse_map(char *file, t_game *game);
bool	validate_map(t_map *map);

// Free functions
void	free_map(t_map *map);
void	free_game(t_game *game);

// Rendering
void	render_map(t_game *game);
void	load_textures(t_game *game);

// Movements and events
void	move_player(t_game *game, int dx, int dy);
void	key_handler(mlx_key_data_t keydata, void *param);

// Error
void	exit_error(const char *msg);
int		print_error(const char *msg, int exit_code);

#endif
