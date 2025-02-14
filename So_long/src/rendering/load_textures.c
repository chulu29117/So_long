/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:50 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 21:02:59 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Load the images for the wall, collectible, exit, floor, and player
// Exits the program if any texture fails the load
void	load_textures(t_game *game)
{
	game->img_wall = mlx_load_xpm42("textures/wall.xpm");
	if (!game->img_wall)
		exit_error("Failed to load wall texture");
	game->img_collectible = mlx_load_xpm42("textures/collectible.xpm");	
	if (!game->img_collectible)
		exit_error("Failed to load collectible textures");
	game->img_exit = mlx_load_xpm42("textures/exit.xpm");
	if (!game->img_exit)
		exit_error("Failed to load exit texture");
	game->img_floor = mlx_load_xpm42("textures/floor.xpm");
	if (!game->img_floor)
		exit_error("Failed to load floor texture");
	game->img_player = mlx_load_xpm42("textures/player.xpm");
	if (!game->img_player)
		exit_error("Failed to load player texture");
}
