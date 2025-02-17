/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:19 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 14:03:18 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == WALL)
				mlx_image_to_window(game->mlx, game->img->wall,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == COLLECT)
				mlx_image_to_window(game->mlx, game->img->collectible,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == EXIT)
				mlx_image_to_window(game->mlx, game->img->exit,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == FLOOR)
				mlx_image_to_window(game->mlx, game->img->floor,
					x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == PLAYER)
				game->player_instance = mlx_image_to_window(game->mlx, 
					game->img->player, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}
