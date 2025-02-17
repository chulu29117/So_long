/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:26 by clu               #+#    #+#             */
/*   Updated: 2025/02/17 14:00:06 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void update_player_position(t_game *game, int new_x, int new_y)
{
	if (!game->img->player)
	{
		ft_printf("Error: img_player->instances is NULL\n");
		return;
	}
	ft_printf("Updating player instance to (%d, %d)\n", new_x * 64, new_y * 64);
	mlx_delete_image(game->mlx, game->img->player);
	game->img->player = mlx_texture_to_image(game->mlx, game->tex->player);
	game->player_instance = mlx_image_to_window(game->mlx, game->img->player, 
		new_x * TILE_SIZE, new_y * TILE_SIZE);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	/* Calculate new player position */
	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	/* Check boundaries and wall collisions */
	if (new_x < 0 || new_x >= game->map_width || 
		new_y < 0 || new_y >= game->map_height)
		return ;
	if (game->map[new_y][new_x] == '1')
		return ;
	/* Update player position and move count */	
	game->player.x = new_x;
	game->player.y = new_y;
	game->move_count++;
	ft_printf("Moves: %d\n", game->move_count);
    update_player_position(game, new_x, new_y);
}
