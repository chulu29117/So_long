/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:21:26 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 22:04:38 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	/* Calculate new player position */
	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	/* Check boundaries and wall collisions */
	if (new_x < 0 || new_x >= game->map.width
		|| new_y < 0 || new_y >= game->map.height)
		return ;
	if (game->map.grid[new_y][new_x] == '1')
		return ;
	/* Update player position and move count */	
	game->player.x = new_x;
	game->player.y = new_y;
	game->move_count++;
	ft_printf("Moves: %d\n", game->move_count);
	render_map(game);
}
