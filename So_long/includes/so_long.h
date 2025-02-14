/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:19:51 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 23:06:30 by clu              ###   ########.fr       */
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
	mlx_image_t	*img_wall;
	mlx_image_t	*img_collectible;
	mlx_image_t	*img_floor;
	mlx_image_t	*img_player;
	mlx_image_t	*img_exit;
	int			move_count;
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
void	hook(void *param);

// Error
void	exit_error(const char *msg);
int		print_error(const char *msg, int exit_code);

#endif
