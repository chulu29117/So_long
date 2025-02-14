/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clu <clu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:32:50 by clu               #+#    #+#             */
/*   Updated: 2025/02/14 23:13:21 by clu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Load the images for the wall, collectible, exit, floor, and player
// Exits the program if any texture fails the load
void	load_textures(t_game *game)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42("textures/wall.xpm42");
	if (!xpm)
		exit_error("Failed to load wall texture");
	game->img_wall = mlx_texture_to_image(game->mlx, &xpm->texture);
	if (!game->img_wall)
		exit_error("Failed to convert wall texture to image");
	mlx_delete_xpm42(xpm);
	xpm = mlx_load_xpm42("textures/collectible.xpm42");
	if (!xpm)
		exit_error("Failed to load collectible texture");
	game->img_collectible = mlx_texture_to_image(game->mlx, &xpm->texture);
	if (!game->img_collectible)
		exit_error("Failed to convert collectible texture to image");
	mlx_delete_xpm42(xpm);
	xpm = mlx_load_xpm42("textures/exit.xpm42");
	if (!xpm)
		exit_error("Failed to load exit texture");
	game->img_exit = mlx_texture_to_image(game->mlx, &xpm->texture);
	if (!game->img_exit)
		exit_error("Failed to convert exit texture to image");
	mlx_delete_xpm42(xpm);
	xpm = mlx_load_xpm42("textures/floor.xpm42");
	if (!xpm)
		exit_error("Failed to load floor texture");
	game->img_floor = mlx_texture_to_image(game->mlx, &xpm->texture);
	if (!game->img_floor)
		exit_error("Failed to convert floor texture to image");
	mlx_delete_xpm42(xpm);
	xpm = mlx_load_xpm42("textures/player.xpm42");
	if (!xpm)
		exit_error("Failed to load player texture");
	game->img_player = mlx_texture_to_image(game->mlx, &xpm->texture);
	if (!game->img_player)
		exit_error("Failed to convert player texture to image");
	mlx_delete_xpm42(xpm);
}
