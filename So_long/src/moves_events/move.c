/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:26 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 16:50:08 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, int dx, int dy)
{
	int	new_tile_x;
	int	new_tile_y;
	int	max_tiles_x;
	int	max_tiles_y;
	int	row;

	// Calculate new position in tile coordinates.
	new_tile_x = game->player.x + dx;
	new_tile_y = game->player.y + dy;
	// Compute maximum tiles in x and y.
	max_tiles_x = ft_strlen(game->map[0]);
	max_tiles_y = 0;
	row = 0;
	while (game->map[row])
	{
		max_tiles_y++;
		row++;
	}
	// Check boundaries in terms of tile counts.
	if (new_tile_x < 0 || new_tile_x >= max_tiles_x ||
		new_tile_y < 0 || new_tile_y >= max_tiles_y)
		return ;
	
	// Check for wall collision (assuming '1' represents a wall).
	if (game->map[new_tile_y][new_tile_x] == '1')
		return ;
	// Update player's logical position and move count.
	game->player.x = new_tile_x;
	game->player.y = new_tile_y;
	game->move_count++;
	ft_printf("MOVES: %i\n", game->move_count);
	// Update the player's image instance's position in pixels.
	game->img->player->instances[game->player_instance].x = new_tile_x * TILE_SIZE;
	game->img->player->instances[game->player_instance].y = new_tile_y * TILE_SIZE;
}

