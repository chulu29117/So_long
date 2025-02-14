/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:19 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 21:09:37 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_game *game)
{
	int	x;
	int	y;
	int	tile_size;

	tile_size = 64;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.height)
		{
			if (game->map.grid[y][x] == '1')
				mlx_image_to_window(game->mlx, game->img_wall,
					x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->img_collectible,
					x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->img_exit,
					x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == '0')
				mlx_image_to_window(game->mlx, game->img_floor,
					x * tile_size, y * tile_size);
			else if (game->map.grid[y][x] == 'P')
				mlx_image_to_window(game->mlx, game->img_player,
					x * tile_size, y * tile_size);
			x++;
		}
		y++;
	}
}
